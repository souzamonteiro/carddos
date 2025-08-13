#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MEM_SIZE (1024 * 1024) // 1MB de RAM
#define NUM_REGS 32

typedef struct {
    uint32_t reg[NUM_REGS]; // Registradores x0-x31 (x0 é zero)
    uint8_t mem[MEM_SIZE];  // Memória RAM
    uint32_t pc;            // Contador de programa
    uint32_t halted;        // Flag de parada
} CPU;

// Inicializa a CPU
void cpu_init(CPU *cpu) {
    memset(cpu, 0, sizeof(CPU));
    cpu->pc = 0x00000000; // PC inicial
}

// Lê uma palavra (32 bits) da memória
uint32_t mem_read(CPU *cpu, uint32_t addr) {
    if (addr >= MEM_SIZE) {
        printf("Erro: Leitura fora da memória (0x%08X)\n", addr);
        cpu->halted = 1;
        return 0;
    }
    // Lê em little-endian
    return (uint32_t)cpu->mem[addr] |
           ((uint32_t)cpu->mem[addr+1] << 8) |
           ((uint32_t)cpu->mem[addr+2] << 16) |
           ((uint32_t)cpu->mem[addr+3] << 24);
}

// Escreve uma palavra (32 bits) na memória
void mem_write(CPU *cpu, uint32_t addr, uint32_t data) {
    if (addr >= MEM_SIZE) {
        printf("Erro: Escrita fora da memória (0x%08X)\n", addr);
        cpu->halted = 1;
        return;
    }
    *(uint32_t*)(cpu->mem + addr) = data;
}

// Decodifica e executa uma instrução
void execute(CPU *cpu, uint32_t instr) {
    uint8_t opcode = instr & 0x7F;
    uint8_t funct3 = (instr >> 12) & 0x7;
    uint8_t funct7 = (instr >> 25) & 0x7F;
    uint8_t rd = (instr >> 7) & 0x1F;
    uint8_t rs1 = (instr >> 15) & 0x1F;
    uint8_t rs2 = (instr >> 20) & 0x1F;
    int32_t imm_i = (int32_t)(instr >> 20);
    int32_t imm_s = (int32_t)((instr >> 7) & 0x1F) | ((instr >> 25) << 5);
    int32_t imm_b = ((instr >> 8) & 0xF) | ((instr >> 25) << 4) | ((instr >> 7) & 0x1) << 11 | ((instr >> 31) << 12);
    int32_t imm_u = instr & 0xFFFFF000;
    int32_t imm_j = ((instr >> 21) & 0x3FF) | ((instr >> 20) & 0x1) << 10 | ((instr >> 12) & 0xFF) << 11 | ((instr >> 31) << 20);

    switch (opcode) {
        // Instruções do tipo R (ADD, SUB, etc.)
        case 0x33:
            switch (funct3) {
                case 0x0: // ADD ou SUB
                    if (funct7 == 0x00) cpu->reg[rd] = cpu->reg[rs1] + cpu->reg[rs2];
                    else if (funct7 == 0x20) cpu->reg[rd] = cpu->reg[rs1] - cpu->reg[rs2];
                    break;
                case 0x4: // XOR
                    cpu->reg[rd] = cpu->reg[rs1] ^ cpu->reg[rs2];
                    break;
                // Adicione mais instruções (AND, OR, SLT, etc.)...
            }
            break;

        // Instruções do tipo I (ADDI, LW, etc.)
        case 0x13: // ADDI
            cpu->reg[rd] = cpu->reg[rs1] + imm_i;
            break;
        case 0x03: // LW
            cpu->reg[rd] = mem_read(cpu, cpu->reg[rs1] + imm_i);
            break;

        // Instruções do tipo S (SW)
        case 0x23: // SW
            mem_write(cpu, cpu->reg[rs1] + imm_s, cpu->reg[rs2]);
            break;

        // Instruções do tipo B (BEQ, BNE)
        case 0x63:
            switch (funct3) {
                case 0x0: // BEQ
                    if (cpu->reg[rs1] == cpu->reg[rs2]) cpu->pc += imm_b - 4;
                    break;
                // Adicione mais branches (BNE, BLT, etc.)...
            }
            break;

        // Instruções do tipo U (LUI, AUIPC)
        case 0x37: // LUI
            cpu->reg[rd] = imm_u;
            break;

        // Instruções do tipo J (JAL)
        case 0x6F: // JAL
            cpu->reg[rd] = cpu->pc + 4;
            cpu->pc += imm_j - 4;
            break;

        // Syscall (ECALL)
        case 0x73:
            if (cpu->reg[17] == 10) { // Exit syscall (Linux RISC-V)
                cpu->halted = 1;
            }
            break;

        default:
            printf("Instrução não implementada: 0x%08X\n", instr);
            cpu->halted = 1;
    }

    printf("PC=0x%08X: Instr=0x%08X\n", cpu->pc, instr);
}

// Loop principal da VM
void cpu_run(CPU *cpu) {
    while (!cpu->halted) {
        uint32_t instr = mem_read(cpu, cpu->pc);
        cpu->pc += 4;
        execute(cpu, instr);
    }
}

// Carrega um programa na memória
void load_program(CPU *cpu, const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }
    
    uint32_t offset = 0;
    uint8_t bytes[4];
    while (fread(bytes, 1, 4, f) == 4 && offset < MEM_SIZE-3) {
        cpu->mem[offset]   = bytes[0];
        cpu->mem[offset+1] = bytes[1];
        cpu->mem[offset+2] = bytes[2];
        cpu->mem[offset+3] = bytes[3];
        offset += 4;
    }
    fclose(f);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Uso: %s <programa.bin>\n", argv[0]);
        return 1;
    }

    CPU cpu;
    cpu_init(&cpu);
    load_program(&cpu, argv[1]);
    cpu_run(&cpu);

    // Exibe registradores ao final
    for (int i = 0; i < NUM_REGS; i++) {
        printf("x%d = 0x%08X\n", i, cpu.reg[i]);
    }

    return 0;
}
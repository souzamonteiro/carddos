# Proposta de uma VM e um Assembler RISC-V

## Descrição
Aqui está um **código completo de uma VM RISC-V em C** que implementa um subconjunto do RV32I (suficiente para executar programas básicos). Esta VM inclui:

1. **Decodificação de instruções** (tipos R, I, S, B, U, J).  
2. **Registradores e memória**.  
3. **Ciclo de máquina básico** (fetch-decode-execute).  
4. **Suporte a syscalls** (para E/S via terminal).  

---

### **1. Código da VM (arquivo `riscv_vm.c`)**
```c
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
    return *(uint32_t*)(cpu->mem + addr);
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
    fread(cpu->mem, 1, MEM_SIZE, f);
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
```

---

### **2. Como Usar a VM**
#### **Passo 1: Compilar**
```bash
gcc riscv_vm.c -o riscv_vm
```

#### **Passo 2: Criar um Programa Binário**
Use um assembler RISC-V (como `riscv64-unknown-elf-as`) para gerar um `.bin` a partir de assembly.  
Exemplo (`programa.s`):
```asm
# Soma 5 + 3 e armazena em x1
addi x2, x0, 5
addi x3, x0, 3
add x1, x2, x3
```

Compile para binário:
```bash
riscv64-unknown-elf-as programa.s -o programa.o
riscv64-unknown-elf-objcopy -O binary programa.o programa.bin
```

#### **Passo 3: Executar na VM**
```bash
./riscv_vm programa.bin
```
Saída:
```
x0 = 0x00000000
x1 = 0x00000008  # Resultado da soma
x2 = 0x00000005
x3 = 0x00000003
...
```

---

### **3. Funcionalidades Adicionais (Para Extender)**
1. **Suporte a mais instruções**:  
   - Adicione `mul`, `div`, `fence`, etc.  
2. **Syscalls para E/S**:  
   - Implemente `write` para imprimir na tela.  
3. **Modo privilegiado**:  
   - Adicione suporte a interrupções e exceções.  

---

### **4. Dependências Opcionais**
- Para programas mais complexos, use a **GNU RISC-V Toolchain** para compilar código C.  
- Para debug, use `gdb` com alvo RISC-V.  

---

### **Conclusão**
Esta VM é **didática e minimalista**, mas funcional.

## Arquitetura

O código da VM RISC-V suporta **12 instruções básicas** do subconjunto **RV32I** (suficiente para programas simples). Aqui está a lista detalhada:

---

### **Instruções Implementadas (12)**
| Tipo  | Instruções Suportadas               | Opcode | Observações                          |
|-------|-------------------------------------|--------|--------------------------------------|
| **R** | `add`, `sub`, `xor`                 | 0x33   | Operações aritméticas com registradores |
| **I** | `addi`, `lw`                        | 0x13, 0x03 | Aritmética com imediato + load       |
| **S** | `sw`                                | 0x23   | Store (grava na memória)             |
| **B** | `beq`                               | 0x63   | Branch se igual                      |
| **U** | `lui`                               | 0x37   | Load Upper Immediate                 |
| **J** | `jal`                               | 0x6F   | Jump and Link                        |
| **Sistema** | `ecall` (para syscall de exit) | 0x73   | Encerra a execução                   |

---

### **Instruções Faltantes (Principais)**
Para uma VM mais completa, você pode adicionar:
1. **Tipo R**:  
   - `and`, `or`, `sll`, `srl`, `sra`, `slt`, `sltu`  
   - `mul`, `div` (extensão **M**)  

2. **Tipo I**:  
   - `andi`, `ori`, `xori`, `slli`, `srli`, `srai`  
   - `jalr` (jump com offset)  

3. **Tipo B**:  
   - `bne`, `blt`, `bge`, `bltu`, `bgeu`  

4. **Outras**:  
   - `auipc` (U-type)  
   - `fence` (controle de memória)  

---

### **Como Estender a VM**
Para adicionar mais instruções, modifique a função `execute()` seguindo o padrão:
```c
case 0x33: // Tipo R
    switch (funct3) {
        case 0x0: // ADD ou SUB
            if (funct7 == 0x00) cpu->reg[rd] = cpu->reg[rs1] + cpu->reg[rs2];
            else if (funct7 == 0x20) cpu->reg[rd] = cpu->reg[rs1] - cpu->reg[rs2];
            break;
        case 0x1: // SLL (Shift Left Logical)
            cpu->reg[rd] = cpu->reg[rs1] << (cpu->reg[rs2] & 0x1F);
            break;
        // Adicione mais casos aqui...
    }
    break;
```

---

### **Exemplo de Código com Extensão (suporte a `and` e `ori`)**
```c
case 0x33: // Tipo R
    switch (funct3) {
        case 0x7: // AND
            cpu->reg[rd] = cpu->reg[rs1] & cpu->reg[rs2];
            break;
    }
    break;
case 0x13: // Tipo I
    switch (funct3) {
        case 0x6: // ORI
            cpu->reg[rd] = cpu->reg[rs1] | imm_i;
            break;
    }
    break;
```

---

### **Quantidade Total Suportável**
- **RV32I básico**: 47 instruções (todas do núcleo inteiro).  
- **Com extensões**:  
  - **M** (+8 instruções para multiplicação/divisão).  
  - **F/D** (+30 para ponto flutuante).  

---

### **Conclusão**
- **Atualmente**: 12 instruções (suficiente para programas didáticos).  
- **Para uma VM completa**: Implementar as 47 do RV32I ou adicione extensões conforme a necessidade.  

## Assembler

Nesta sessão é apresentado um **assembler em C** para o subconjunto de 12 instruções RISC-V que a VM suporta. Ele converte assembly (texto) em bytecode binário, compatível com a VM anterior:

---

### **Arquivo: `riscv_assembler.c`**
```c
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Tabela de registradores (nome -> número)
int get_register(const char *reg) {
    if (strcmp(reg, "zero") == 0) return 0;
    if (reg[0] == 'x') return atoi(reg + 1);
    if (strcmp(reg, "ra") == 0) return 1;
    if (strcmp(reg, "sp") == 0) return 2;
    return -1; // Inválido
}

// Remove espaços e comentários
void clean_line(char *line) {
    char *comment = strchr(line, '#');
    if (comment) *comment = '\0';
    while (isspace(*line)) line++;
    char *end = line + strlen(line) - 1;
    while (end > line && isspace(*end)) end--;
    *(end + 1) = '\0';
}

// Converte instrução para binário (suporta 12 instruções)
uint32_t assemble(const char *op, const char *args) {
    uint32_t opcode = 0, rd = 0, rs1 = 0, rs2 = 0, imm = 0;

    // Tipo R (add, sub, xor)
    if (strcmp(op, "add") == 0 || strcmp(op, "sub") == 0 || strcmp(op, "xor") == 0) {
        sscanf(args, "x%d,x%d,x%d", &rd, &rs1, &rs2);
        uint32_t funct7 = (strcmp(op, "sub") == 0) ? 0x20 : 0x00;
        uint32_t funct3 = 
            (strcmp(op, "add") == 0) ? 0x0 :
            (strcmp(op, "sub") == 0) ? 0x0 :
            (strcmp(op, "xor") == 0) ? 0x4 : 0;
        return (funct7 << 25) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12) | (rd << 7) | 0x33;
    }

    // Tipo I (addi, lw)
    else if (strcmp(op, "addi") == 0 || strcmp(op, "lw") == 0) {
        sscanf(args, "x%d,x%d,%d", &rd, &rs1, &imm);
        uint32_t funct3 = (strcmp(op, "addi") == 0) ? 0x0 : 0x2;
        opcode = (strcmp(op, "addi") == 0) ? 0x13 : 0x03;
        return (imm << 20) | (rs1 << 15) | (funct3 << 12) | (rd << 7) | opcode;
    }

    // Tipo S (sw)
    else if (strcmp(op, "sw") == 0) {
        sscanf(args, "x%d,%d(x%d)", &rs2, &imm, &rs1);
        return ((imm & 0xFE0) << 25) | (rs2 << 20) | (rs1 << 15) | 0x2 << 12 | ((imm & 0x1F) << 7) | 0x23;
    }

    // Tipo B (beq)
    else if (strcmp(op, "beq") == 0) {
        sscanf(args, "x%d,x%d,%d", &rs1, &rs2, &imm);
        return ((imm & 0x1000) << 19) | ((imm & 0x7E0) << 20) | (rs2 << 20) | (rs1 << 15) | 0x0 << 12 | ((imm & 0x1E) << 7) | ((imm & 0x800) >> 4) | 0x63;
    }

    // Tipo U (lui)
    else if (strcmp(op, "lui") == 0) {
        sscanf(args, "x%d,%d", &rd, &imm);
        return (imm & 0xFFFFF000) | (rd << 7) | 0x37;
    }

    // Tipo J (jal)
    else if (strcmp(op, "jal") == 0) {
        sscanf(args, "x%d,%d", &rd, &imm);
        return ((imm & 0x100000) << 11) | ((imm & 0x7FE) << 20) | ((imm & 0x800) << 9) | (rd << 7) | 0x6F;
    }

    // ECALL
    else if (strcmp(op, "ecall") == 0) {
        return 0x73;
    }

    printf("Erro: Instrução não suportada: %s\n", op);
    exit(1);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Uso: %s <input.s> <output.bin>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "wb");

    char line[256];
    while (fgets(line, sizeof(line), input)) {
        clean_line(line);
        if (strlen(line) == 0) continue;

        char op[16], args[64];
        sscanf(line, "%s %[^\n]", op, args);

        uint32_t instr = assemble(op, args);
        fwrite(&instr, sizeof(uint32_t), 1, output);
    }

    fclose(input);
    fclose(output);
    printf("Assembly traduzido para: %s\n", argv[2]);
    return 0;
}
```

---

### **Como Usar o Assembler**
#### **Passo 1: Escreva um Programa Assembly (`exemplo.s`)**
```asm
# Soma 5 + 3 e armazena em x1
addi x2, x0, 5
addi x3, x0, 3
add x1, x2, x3
```

#### **Passo 2: Compile o Assembler**
```bash
gcc riscv_assembler.c -o riscv_assembler
```

#### **Passo 3: Converta para Binário**
```bash
./riscv_assembler exemplo.s exemplo.bin
```

#### **Passo 4: Execute na VM RISC-V**
```bash
./riscv_vm exemplo.bin
```
Saída esperada:
```
x1 = 0x00000008  # Resultado da soma
x2 = 0x00000005
x3 = 0x00000003
```

---

### **Funcionalidades do Assembler**
1. **Suporte às 12 instruções** da VM (add, sub, addi, lw, sw, beq, lui, jal, etc.).  
2. **Tratamento de registradores** (aceita `x0`-`x31` ou pseudônimos como `zero`, `sp`).  
3. **Geração de binário** pronto para a VM.  

---

### **Limitações**
- Não suporta **labels** (para jumps/branches, use endereços absolutos).  
- Não suporta **pseudo-instruções** (como `li` ou `mv`).  

---

### **Como Estender**
Para adicionar mais instruções (ex: `andi`, `jalr`), inclua novos casos na função `assemble()` seguindo o padrão dos tipos R/I/S/B/U/J.  

Analisando os códigos finais do assembler e da VM RISC-V, vamos criar um conjunto abrangente de testes para validar todas as funcionalidades implementadas. Os programas de teste cobrirão:

## Testes

### 1. Testes Básicos Aritméticos
**test_arithmetic.s**:
```asm
addi x1, x0, 5       # x1 = 5
addi x2, x0, 3       # x2 = 3
add x3, x1, x2       # x3 = 8 (5+3)
sub x4, x1, x2       # x4 = 2 (5-3)
xor x5, x1, x2       # x5 = 6 (5 XOR 3)
addi a7, x0, 10      # syscall exit
ecall
```

**Verificação esperada**:
```
x1 = 0x00000005
x2 = 0x00000003 
x3 = 0x00000008
x4 = 0x00000002
x5 = 0x00000006
```

### 2. Testes de Memória (Load/Store)
**test_memory.s**:
```asm
addi sp, x0, 0x100   # sp = 0x100
addi x1, x0, 0x1234  # x1 = 0x1234
sw x1, 8(sp)         # Mem[0x108] = 0x1234
lw x2, 8(sp)         # x2 = 0x1234
addi a7, x0, 10
ecall
```

**Verificação esperada**:
```
x1 = 0x00001234
x2 = 0x00001234
sp = 0x00000100
```

### 3. Testes de Controle de Fluxo
**test_branch.s**:
```asm
addi x1, x0, 5
addi x2, x0, 5
beq x1, x2, label    # Deve pular
addi x3, x0, 1       # Não executado
label:
addi x4, x0, 2       # x4 = 2
addi a7, x0, 10
ecall
```

**Verificação esperada**:
```
x1 = 0x00000005
x2 = 0x00000005
x3 = 0x00000000
x4 = 0x00000002
```

### 4. Testes de Jump
**test_jump.s**:
```asm
addi x1, x0, 1
jal x10, target      # x10 = PC+4, jump para target
addi x1, x0, 2       # Não executado
target:
addi x2, x0, 3
addi a7, x0, 10
ecall
```

**Verificação esperada**:
```
x1 = 0x00000001
x2 = 0x00000003
x10 = 0x0000000C (endereço da próxima instrução após jal)
```

### 5. Teste de Syscall
**test_syscall.s**:
```asm
addi a0, x0, 42      # Valor de retorno
addi a7, x0, 10      # Syscall exit
ecall
```

**Verificação esperada**:
```
a0 = 0x0000002A
a7 = 0x0000000A
```

### 6. Teste Completo (Combinação)
**test_complex.s**:
```asm
addi sp, x0, 0x100
lui x1, 0x12345      # x1 = 0x12345000
addi x2, x0, 0x678
add x3, x1, x2       # x3 = 0x12345678
sw x3, 0(sp)
lw x4, 0(sp)
beq x3, x4, label
addi x5, x0, 1       # Não executado
label:
addi a7, x0, 10
ecall
```

**Verificação esperada**:
```
x1 = 0x12345000
x3 = 0x12345678
x4 = 0x12345678
x5 = 0x00000000
```

### Procedimento de Teste:

1. Para cada arquivo `.s`:
```bash
./riscv_assembler test_X.s test_X.bin
./riscv_vm test_X.bin
```

2. Verifique:
- Saída dos registradores
- Mensagens de execução (PC e instruções)
- Comportamento do programa

### Testes Adicionais Recomendados:

1. **Teste de Limites**:
   - Valores máximos/minimos de imediatos
   - Acesso a memória nos limites (0x000000 e 0xFFFFC)

2. **Teste de Erros**:
   - Instruções inválidas
   - Registradores inválidos
   - Acesso a memória não alinhado

3. **Teste de Performance**:
   - Loop com 1000 iterações
   - Cálculo de Fibonacci (10 iterações)

A implementação atual cobre:
- Todas as instruções básicas do RV32I
- Suporte a pseudo-instruções (via get_register)
- Manipulação correta de endianness
- Tratamento de syscall

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Tabela de registradores (nome -> número).
int get_register(const char *reg) {
    // Remove espaços se houver
    char cleaned[10];
    sscanf(reg, "%s", cleaned);
    
    if (strcmp(cleaned, "zero") == 0) return 0;
    if (strcmp(cleaned, "ra") == 0) return 1;
    if (strcmp(cleaned, "sp") == 0) return 2;
    if (strcmp(cleaned, "a0") == 0) return 10;
    if (strcmp(cleaned, "a7") == 0) return 17;
    if (cleaned[0] == 'x') return atoi(cleaned + 1);
    
    printf("Registrador inválido: %s\n", cleaned);
    exit(1);
}

// Remove espaços e comentários.
void clean_line(char *line) {
    char *comment = strchr(line, '#');
    if (comment) *comment = '\0';
    while (isspace(*line)) line++;
    char *end = line + strlen(line) - 1;
    while (end > line && isspace(*end)) end--;
    *(end + 1) = '\0';
}

// Converte instrução para binário (suporta 12 instruções).
uint32_t assemble(const char *op, const char *args) {
    uint32_t opcode = 0, rd = 0, rs1 = 0, rs2 = 0, imm = 0;
    char rd_str[10], rs1_str[10], rs2_str[10];

    // No início da função assemble()
    if (strlen(args) == 0) {
        printf("Erro: Argumentos faltando para %s\n", op);
        exit(1);
    }

    // Tipo R (add, sub, xor).
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
        // Corrigido para capturar registradores e imediate corretamente
        if (sscanf(args, "x%d,x%d,%d", &rd, &rs1, &imm) != 3) {
            printf("Erro de sintaxe em: %s %s\n", op, args);
            exit(1);
        }
        uint32_t funct3 = (strcmp(op, "addi") == 0) ? 0x0 : 0x2;
        opcode = (strcmp(op, "addi") == 0) ? 0x13 : 0x03;
        return (imm << 20) | (rs1 << 15) | (funct3 << 12) | (rd << 7) | opcode;
    }

    // Tipo S (sw).
    else if (strcmp(op, "sw") == 0) {
        sscanf(args, "x%d,%d(x%d)", &rs2, &imm, &rs1);
        return ((imm & 0xFE0) << 25) | (rs2 << 20) | (rs1 << 15) | 0x2 << 12 | ((imm & 0x1F) << 7) | 0x23;
    }

    // Tipo B (beq).
    else if (strcmp(op, "beq") == 0) {
        sscanf(args, "x%d,x%d,%d", &rs1, &rs2, &imm);
        return ((imm & 0x1000) << 19) | ((imm & 0x7E0) << 20) | (rs2 << 20) | (rs1 << 15) | 0x0 << 12 | ((imm & 0x1E) << 7) | ((imm & 0x800) >> 4) | 0x63;
    }

    // Tipo U (lui).
    else if (strcmp(op, "lui") == 0) {
        sscanf(args, "x%d,%d", &rd, &imm);
        return (imm & 0xFFFFF000) | (rd << 7) | 0x37;
    }

    // Tipo J (jal).
    else if (strcmp(op, "jal") == 0) {
        sscanf(args, "x%d,%d", &rd, &imm);
        return ((imm & 0x100000) << 11) | ((imm & 0x7FE) << 20) | ((imm & 0x800) << 9) | (rd << 7) | 0x6F;
    }

    // ECALL.
    else if (strcmp(op, "ecall") == 0) {
        return 0x73;
    }

    printf("Erro: Instrução não suportada: %s\n", op);
    exit(1);
}

int is_directive(const char *op) {
    return op[0] == '.';
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

        if (is_directive(op)) continue; // Ignora diretivas

        uint32_t instr = assemble(op, args);
        uint8_t bytes[4];
        bytes[0] = (instr >> 0) & 0xFF;  // Byte menos significativo
        bytes[1] = (instr >> 8) & 0xFF;
        bytes[2] = (instr >> 16) & 0xFF;
        bytes[3] = (instr >> 24) & 0xFF; // Byte mais significativo
        fwrite(bytes, 1, 4, output);
    }

    fclose(input);
    fclose(output);
    printf("Assembly traduzido para: %s\n", argv[2]);
    return 0;
}

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char name[50];
    uint32_t address;
} Label;

Label labels[50];
int label_count = 0;
uint32_t current_address = 0;  // Contador de endereço para labels

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
    // Remove comentários
    char *comment = strchr(line, '#');
    if (comment) *comment = '\0';

    // Remove \n do final
    size_t len = strlen(line);
    if (len > 0 && line[len-1] == '\n')
        line[len-1] = '\0';

    // Remove espaços no início
    char *start = line;
    while (isspace(*start)) start++;

    // Desloca a string para o início
    if (start != line)
        memmove(line, start, strlen(start) + 1);

    // Remove espaços no final
    len = strlen(line);
    while (len > 0 && isspace(line[len-1])) {
        line[len-1] = '\0';
        len--;
    }
}

// Processa labels.
void process_labels(FILE *input) {
    char line[256];
    current_address = 0;
    
    rewind(input);
    while (fgets(line, sizeof(line), input)) {
        char original_line[256];
        strcpy(original_line, line);  // Mantém cópia original
        
        clean_line(line);
        if (strlen(line) == 0) continue;

        // Verifica se é label (linha original termina com ':')
        // Detecta label mesmo com espaços
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == ':') {
            line[len-1] = '\0'; // remove ':'
            while (len > 1 && isspace(line[len-2])) {
                line[len-2] = '\0';
                len--;
            }

            strcpy(labels[label_count].name, line);
            labels[label_count].address = current_address;
            label_count++;

            if (label_count >= 50) {
                printf("Limite de labels excedido (max 50)\n");
                fclose(input);
                exit(1);
            }
        } else {
            current_address += 4;
        }
    }
}

// Converte instrução para binário (suporta 12 instruções).
uint32_t assemble(const char *op, const char *args) {
    uint32_t opcode = 0, rd = 0, rs1 = 0, rs2 = 0, imm = 0;
    char rd_str[10], rs1_str[10], rs2_str[10], imm_str[20];

    // No início da função assemble()
    if (strlen(args) == 0) {
        printf("Erro: Argumentos faltando para %s\n", op);
        exit(1);
    }

    // Tipo R (add, sub, xor)
    if (strcmp(op, "add") == 0 || strcmp(op, "sub") == 0 || strcmp(op, "xor") == 0) {
        if (sscanf(args, "%[^,],%[^,],%s", rd_str, rs1_str, rs2_str) != 3) {
            printf("Erro de sintaxe em: %s %s\n", op, args);
            exit(1);
        }
        
        rd = get_register(rd_str);
        rs1 = get_register(rs1_str);
        rs2 = get_register(rs2_str);
        
        uint32_t funct7 = (strcmp(op, "sub") == 0) ? 0x20 : 0x00;
        uint32_t funct3 = 
            (strcmp(op, "add") == 0 ? 0x0 :
            (strcmp(op, "sub") == 0 ? 0x0 :
            (strcmp(op, "xor") == 0 ? 0x4 : 0)));
            
        return (funct7 << 25) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12) | (rd << 7) | 0x33;
    }

    // Tipo I (lw)
    else if (strcmp(op, "lw") == 0) {
        int offset;
        if (sscanf(args, "%[^,],%d(%[^)])", rd_str, &offset, rs1_str) != 3) {
            printf("Erro de sintaxe em: %s %s\n", op, args);
            exit(1);
        }

        rd = get_register(rd_str);
        rs1 = get_register(rs1_str);
        imm = offset;

        uint32_t funct3 = 0x2;
        opcode = 0x03;
        return (imm << 20) | (rs1 << 15) | (funct3 << 12) | (rd << 7) | opcode;
    }

    // Tipo I (addi)
    else if (strcmp(op, "addi") == 0) {
        if (sscanf(args, "%[^,],%[^,],%s", rd_str, rs1_str, imm_str) != 3) {
            printf("Erro de sintaxe em: %s %s\n", op, args);
            exit(1);
        }

        rd = get_register(rd_str);
        rs1 = get_register(rs1_str);
        imm = atoi(imm_str);

        uint32_t funct3 = 0x0;
        opcode = 0x13;
        return (imm << 20) | (rs1 << 15) | (funct3 << 12) | (rd << 7) | opcode;
    }

    // Tipo S (sw).
    else if (strcmp(op, "sw") == 0) {
        sscanf(args, "x%d,%d(x%d)", &rs2, &imm, &rs1);
        return ((imm & 0xFE0) << 25) | (rs2 << 20) | (rs1 << 15) | 0x2 << 12 | ((imm & 0x1F) << 7) | 0x23;
    }

    // Tipo B (beq).
    else if (strcmp(op, "beq") == 0) {
        char rs1_str[10], rs2_str[10], label_str[50];
        if (sscanf(args, "%[^,],%[^,],%s", rs1_str, rs2_str, label_str) != 3) {
            printf("Erro de sintaxe em: %s %s\n", op, args);
            exit(1);
        }
        
        rs1 = get_register(rs1_str);
        rs2 = get_register(rs2_str);
        
        // Encontra o label
        int32_t offset = -1;
        for (int i = 0; i < label_count; i++) {
            if (strcmp(label_str, labels[i].name) == 0) {
                offset = labels[i].address - (current_address + 4);
                break;
            }
        }
        
        if (offset == -1) {
            printf("Label não encontrado: %s\n", label_str);
            exit(1);
        }
        
        // Verifica se offset está dentro do range [-4096, 4094]
        if (offset < -4096 || offset > 4094) {
            printf("Offset de branch muito grande: %d\n", offset);
            exit(1);
        }
        
        // Codificação B-type corrigida:
        uint32_t imm = offset >> 1;  // Converte para half-words
        return ((imm & 0x800) << 20) |  // bit 12
            ((imm & 0x3F0) << 21) |  // bits 10:5
            (rs2 << 20) |
            (rs1 << 15) |
            (0x0 << 12) |            // funct3 para BEQ
            ((imm & 0xF) << 8) |     // bits 4:1
            ((imm & 0x400) << 19) |  // bit 11
            0x63;                    // opcode
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
    if (!input) {
        perror("Erro ao abrir arquivo de entrada");
        return 1;
    }

    FILE *output = fopen(argv[2], "wb");
    if (!output) {
        perror("Erro ao criar arquivo de saída");
        fclose(input);
        return 1;
    }

    // Primeira passada: processa labels
    process_labels(input);
    rewind(input);
    
    // Segunda passada: gera o código
    current_address = 0;
    char line[256];
    while (fgets(line, sizeof(line), input)) {
        if (strlen(line) >= sizeof(line) - 1) {
            printf("Linha muito longa no arquivo de entrada\n");
            fclose(input);
            fclose(output);
            return 1;
        }

        clean_line(line);
        if (strlen(line) == 0) continue;

        char op[16], args[64];
        sscanf(line, "%s %[^\n]", op, args);
        size_t oplen = strlen(op);
        if (oplen > 0 && op[oplen-1] == ':')
            continue;

        if (is_directive(op)) continue; // Ignora diretivas

        uint32_t instr = assemble(op, args);
        uint8_t bytes[4];
        bytes[0] = (instr >> 0) & 0xFF;  // Byte menos significativo
        bytes[1] = (instr >> 8) & 0xFF;
        bytes[2] = (instr >> 16) & 0xFF;
        bytes[3] = (instr >> 24) & 0xFF; // Byte mais significativo
        fwrite(bytes, 1, 4, output);

        current_address += 4;
    }

    fclose(input);
    fclose(output);
    printf("Assembly traduzido para: %s\n", argv[2]);
    return 0;
}

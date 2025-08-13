# Introdução ao RISC-V  

## Introdução
### O que é RISC-V?  

RISC-V (pronuncia-se "risk-five") é uma arquitetura de conjunto de instruções (ISA, do inglês *Instruction Set Architecture*) aberta e livre, baseada nos princípios da computação de conjunto de instruções reduzido (RISC). Diferente de arquiteturas proprietárias como x86 (Intel/AMD) ou ARM, o RISC-V é desenvolvido sob uma licença de código aberto, permitindo que qualquer pessoa possa implementá-lo, modificá-lo e utilizá-lo sem pagar royalties.  

### História e Origem  

O RISC-V foi originalmente desenvolvido na Universidade da Califórnia, Berkeley, a partir de 2010, como parte de um projeto de pesquisa em arquiteturas de computadores. Seu design foi pensado para ser modular, escalável e adaptável a diferentes aplicações, desde sistemas embarcados até supercomputadores.  

Em 2015, foi criada a **RISC-V Foundation** (hoje chamada **RISC-V International**), uma organização sem fins lucrativos que supervisiona o desenvolvimento e a padronização da arquitetura. Desde então, o RISC-V tem ganhado grande adoção na indústria, academia e comunidade de hardware aberto.  

### Principais Características  

1. **Aberto e Livre**  
   - Não requer licenciamento ou pagamento de royalties.  
   - Permite personalização e extensão conforme necessário.  

2. **Modular e Extensível**  
   - O núcleo base (conjunto de instruções inteiras) é simples, mas pode ser estendido com instruções adicionais (como ponto flutuante, vetoriais, etc.).  
   - Suporta diferentes larguras de dados (32, 64 ou 128 bits).  

3. **Simplicidade e Eficiência**  
   - Segue a filosofia RISC, com instruções decodificadas de forma simples e pipeline eficiente.  
   - Ideal para implementações em FPGA, ASICs e microcontroladores.  

4. **Portabilidade e Ecossistema Crescente**  
   - Várias ferramentas de desenvolvimento disponíveis (compiladores como GCC e LLVM, simuladores como QEMU, etc.).  
   - Suportado por sistemas operacionais como Linux, FreeRTOS e seL4.  

### Aplicações do RISC-V  

O RISC-V está sendo utilizado em diversos segmentos, incluindo:  
- **Dispositivos Embarcados**: Microcontroladores para IoT e wearables.  
- **Computação de Alto Desempenho**: Processadores para servidores e supercomputadores.  
- **Segurança e Criptografia**: Chips dedicados a aplicações seguras.  
- **Educação e Pesquisa**: Facilita o ensino de arquitetura de computadores.  

### Vantagens em Relação a Outras Arquiteturas  

| Característica       | RISC-V       | ARM          | x86          |  
|----------------------|--------------|--------------|--------------|  
| **Licenciamento**    | Aberto       | Proprietário | Proprietário |  
| **Customização**     | Alta         | Limitada     | Muito limitada |  
| **Complexidade**     | Baixa        | Moderada     | Alta         |  
| **Custo**           | Baixo        | Médio/Alto   | Alto         |  

### Conclusão  

O RISC-V representa uma revolução no mundo da arquitetura de processadores, oferecendo liberdade, flexibilidade e eficiência. Com um ecossistema em rápido crescimento, ele se posiciona como uma alternativa viável às arquiteturas tradicionais, especialmente em aplicações que demandam customização e baixo custo.  

Para quem deseja aprender mais, recomenda-se explorar a documentação oficial da **RISC-V International**, além de ferramentas como o **RISC-V GNU Toolchain** e simuladores como **Spike** e **QEMU**.  

## Arquitetura RISC-V
### **1. Visão Geral da Arquitetura RISC-V**  
RISC-V é uma arquitetura de conjunto de instruções (ISA) baseada no modelo **RISC** (*Reduced Instruction Set Computer*), desenvolvida para ser **aberta, modular e extensível**. Sua especificação é mantida pela **RISC-V International**, e sua implementação pode variar desde microcontroladores simples até CPUs de alto desempenho.  

#### **1.1 Princípios de Design**  
- **Simplicidade**: Instruções fixas e decodificação fácil para eficiência em *pipeline*.  
- **Extensibilidade**: ISA modular com conjuntos de instruções opcionais.  
- **Sem Modos de Execução Legados**: Evita complexidade de compatibilidade retroativa.  
- **Suporte a 32, 64 e 128 bits**: Diferentes larguras de dados (RV32, RV64, RV128).  

---

### **2. Conjuntos de Instruções Base e Extensões**  
O RISC-V define um **núcleo base obrigatório** e **extensões opcionais**, permitindo personalização conforme a aplicação.  

#### **2.1 Conjuntos Base**  
- **RV32I**: Operações inteiras de 32 bits (registradores de 32 bits).  
- **RV64I**: Extensão para 64 bits (registradores de 64 bits).  
- **RV128I**: Suporte experimental para 128 bits.  

Cada conjunto base inclui:  
- Operações aritméticas (`ADD`, `SUB`, `AND`, `OR`, `XOR`).  
- Acesso à memória (`LW`, `SW`).  
- Controle de fluxo (`BEQ`, `JAL`).  

#### **2.2 Extensões Padronizadas**  
| Extensão | Descrição |  
|----------|-----------|  
| **M**    | Multiplicação/Divisão (`MUL`, `DIV`). |  
| **A**    | Atômicas para multi-core (`LR.W`, `SC.W`). |  
| **F**    | Ponto flutuante single-precision (32-bit). |  
| **D**    | Ponto flutuante double-precision (64-bit). |  
| **C**    | Instruções compactas (16-bit para reduzir código). |  
| **V**    | Vetorização (SIMD para processamento paralelo). |  
| **B**    | Operações bit-manipulation (útil para criptografia). |  

Exemplo de um perfil comum: **RV64IMAFDC** (64 bits + multiplicação + ponto flutuante + compactação).  

---

### **3. Organização dos Registradores**  
- **32 Registradores Inteiros** (`x0` a `x31`), onde:  
  - `x0`: Sempre zero (hardwired).  
  - `x1` (`ra`): Endereço de retorno.  
  - `x2` (`sp`): Stack pointer.  
  - `x5-x7`, `x10-x17`: Temporários.  
- **Registradores de Ponto Flutuante** (se extensão F/D estiver presente): `f0` a `f31`.  
- **Registradores de Controle**: Como `pc` (contador de programa) e `csr` (registradores de status).  

---

### **4. Modos de Endereçamento e Tipos de Instruções**  
#### **4.1 Formatos de Instrução**  
Todas as instruções RISC-V têm **32 bits** (ou 16, se extensão **C** for usada) e seguem seis formatos:  

| Tipo | Formato | Exemplo |  
|------|---------|---------|  
| **R** (Register) | `opcode rd, rs1, rs2` | `ADD x1, x2, x3` |  
| **I** (Immediate) | `opcode rd, rs1, imm` | `ADDI x1, x2, 10` |  
| **S** (Store) | `opcode rs1, rs2, imm` | `SW x1, 4(x2)` |  
| **B** (Branch) | `opcode rs1, rs2, imm` | `BEQ x1, x2, label` |  
| **U** (Upper Immediate) | `opcode rd, imm` | `LUI x1, 0x1000` |  
| **J** (Jump) | `opcode rd, imm` | `JAL x1, offset` |  

#### **4.2 Modos de Endereçamento**  
- **Imediato**: `ADDI x1, x2, 5` (usa valor constante).  
- **Base + Deslocamento**: `LW x1, 8(x2)` (acesso à memória).  
- **PC-Relativo**: `BEQ x1, x2, label` (desvio condicional).  

---

### **5. Pipeline e Eficiência**  
O RISC-V foi projetado para facilitar implementações **pipelined** eficientes:  
- **Estágios típicos**: Fetch → Decode → Execute → Memory → Writeback.  
- **Sem hazards estruturais**: Graças ao design ortogonal.  
- **Suporte a *out-of-order* e *superscalar*** em implementações avançadas.  

---

### **6. Sistemas de Memória e Privilege Levels**  
#### **6.1 Espaço de Endereçamento**  
- **Memória mapeada em bytes**, com alinhamento opcional.  
- **Little-endian** (padrão, mas big-endian é opcional em algumas implementações).  

#### **6.2 Níveis de Privilégio**  
| Nível | Descrição |  
|-------|-----------|  
| **U** (User) | Aplicações usuárias. |  
| **S** (Supervisor) | Sistema operacional/hypervisor. |  
| **M** (Machine) | Firmware/baixo nível (sempre presente). |  

- **CSRs (Control and Status Registers)**: Configuram interrupções, exceções e virtualização.  

---

### **7. Ferramentas e Ecossistema**  
- **Compiladores**: GCC (`riscv64-unknown-elf-gcc`), LLVM.  
- **Simuladores**: QEMU, Spike (RISC-V ISA Simulator).  
- **Kernels suportados**: Linux, FreeRTOS, seL4.  
- **FPGAs**: Suporte em Xilinx, Intel (Quartus), e ferramentas open-source (Yosys).  

---

### **8. Comparação com Outras Arquiteturas**  
| Critério | RISC-V | ARM | x86 |  
|----------|--------|-----|-----|  
| **Licença** | Aberta | Proprietária | Proprietária |  
| **Extensibilidade** | Alta | Moderada | Baixa |  
| **Complexidade** | Baixa | Média | Alta |  
| **Uso em IoT/Embarcados** | Crescente | Dominante | Raro |  
| **High-Performance** | Emergente (Ex: SiFive, Ventana) | Dominante (ARM Neoverse) | Dominante (Intel/AMD) |  

---

### **9. Conclusão**  
O RISC-V é uma arquitetura **flexível, aberta e eficiente**, adequada para aplicações que vão desde microcontroladores até CPUs de alto desempenho. Sua modularidade permite otimizações específicas, e seu ecossistema está em rápida expansão.  

## **Referência Completa das Instruções RISC-V**  

Esta seção lista todas as instruções do RISC-V, organizadas por categoria, incluindo o conjunto base (**RV32I/RV64I**) e extensões padrão (**M, A, F, D, C, B, V**).  

---

### **1. Instruções do Conjunto Base (RV32I/RV64I)**  

#### **1.1 Instruções Aritméticas e Lógicas**  
| Instrução | Operação | Formato | Descrição |  
|-----------|----------|---------|-----------|  
| `ADD rd, rs1, rs2` | rd = rs1 + rs2 | R | Soma inteira |  
| `SUB rd, rs1, rs2` | rd = rs1 - rs2 | R | Subtração inteira |  
| `ADDI rd, rs1, imm` | rd = rs1 + imm | I | Soma com imediato |  
| `AND rd, rs1, rs2` | rd = rs1 & rs2 | R | AND lógico |  
| `OR rd, rs1, rs2` | rd = rs1 \| rs2 | R | OR lógico |  
| `XOR rd, rs1, rs2` | rd = rs1 ^ rs2 | R | XOR lógico |  
| `ANDI rd, rs1, imm` | rd = rs1 & imm | I | AND com imediato |  
| `ORI rd, rs1, imm` | rd = rs1 \| imm | I | OR com imediato |  
| `XORI rd, rs1, imm` | rd = rs1 ^ imm | I | XOR com imediato |  
| `SLT rd, rs1, rs2` | rd = (rs1 < rs2) ? 1 : 0 | R | Comparação (signed) |  
| `SLTU rd, rs1, rs2` | rd = (rs1 < rs2) ? 1 : 0 | R | Comparação (unsigned) |  
| `SLTI rd, rs1, imm` | rd = (rs1 < imm) ? 1 : 0 | I | SLT com imediato |  
| `SLTIU rd, rs1, imm` | rd = (rs1 < imm) ? 1 : 0 | I | SLTU com imediato |  

#### **1.2 Deslocamentos (Shifts)**  
| Instrução | Operação | Formato | Descrição |  
|-----------|----------|---------|-----------|  
| `SLL rd, rs1, rs2` | rd = rs1 << rs2 | R | Shift lógico à esquerda |  
| `SRL rd, rs1, rs2` | rd = rs1 >> rs2 | R | Shift lógico à direita |  
| `SRA rd, rs1, rs2` | rd = rs1 >> rs2 | R | Shift aritmético à direita |  
| `SLLI rd, rs1, shamt` | rd = rs1 << shamt | I | SLL com imediato |  
| `SRLI rd, rs1, shamt` | rd = rs1 >> shamt | I | SRL com imediato |  
| `SRAI rd, rs1, shamt` | rd = rs1 >> shamt | I | SRA com imediato |  

#### **1.3 Acesso à Memória (Load/Store)**  
| Instrução | Operação | Formato | Descrição |  
|-----------|----------|---------|-----------|  
| `LW rd, offset(rs1)` | rd = Mem[rs1 + offset] | I | Load word (32 bits) |  
| `LD rd, offset(rs1)` | rd = Mem[rs1 + offset] | I | Load doubleword (RV64) |  
| `SW rs2, offset(rs1)` | Mem[rs1 + offset] = rs2 | S | Store word |  
| `SD rs2, offset(rs1)` | Mem[rs1 + offset] = rs2 | S | Store doubleword (RV64) |  

#### **1.4 Controle de Fluxo (Branches/Jumps)**  
| Instrução | Operação | Formato | Descrição |  
|-----------|----------|---------|-----------|  
| `BEQ rs1, rs2, offset` | if (rs1 == rs2) PC += offset | B | Branch if equal |  
| `BNE rs1, rs2, offset` | if (rs1 != rs2) PC += offset | B | Branch if not equal |  
| `BLT rs1, rs2, offset` | if (rs1 < rs2) PC += offset | B | Branch if less (signed) |  
| `BGE rs1, rs2, offset` | if (rs1 >= rs2) PC += offset | B | Branch if greater/equal (signed) |  
| `BLTU rs1, rs2, offset` | if (rs1 < rs2) PC += offset | B | Branch if less (unsigned) |  
| `BGEU rs1, rs2, offset` | if (rs1 >= rs2) PC += offset | B | Branch if greater/equal (unsigned) |  
| `JAL rd, offset` | rd = PC+4; PC += offset | J | Jump and link |  
| `JALR rd, rs1, offset` | rd = PC+4; PC = rs1 + offset | I | Jump and link register |  

#### **1.5 Instruções de Constantes**  
| Instrução | Operação | Formato | Descrição |  
|-----------|----------|---------|-----------|  
| `LUI rd, imm` | rd = imm << 12 | U | Load upper immediate |  
| `AUIPC rd, imm` | rd = PC + (imm << 12) | U | Add upper immediate to PC |  

---

### **2. Extensão de Multiplicação/Divisão (M)**  
| Instrução | Operação | Formato | Descrição |  
|-----------|----------|---------|-----------|  
| `MUL rd, rs1, rs2` | rd = rs1 * rs2 (low bits) | R | Multiplicação |  
| `MULH rd, rs1, rs2` | rd = (rs1 * rs2) >> XLEN | R | Multiplicação (high bits, signed) |  
| `MULHU rd, rs1, rs2` | rd = (rs1 * rs2) >> XLEN | R | Multiplicação (high bits, unsigned) |  
| `DIV rd, rs1, rs2` | rd = rs1 / rs2 (signed) | R | Divisão inteira |  
| `DIVU rd, rs1, rs2` | rd = rs1 / rs2 (unsigned) | R | Divisão unsigned |  
| `REM rd, rs1, rs2` | rd = rs1 % rs2 (signed) | R | Resto da divisão |  
| `REMU rd, rs1, rs2` | rd = rs1 % rs2 (unsigned) | R | Resto unsigned |  

---

### **3. Extensão de Instruções Compactas (C)**  
| Instrução | Equivalente RV32I | Descrição |  
|-----------|------------------|-----------|  
| `C.ADD rd, rs2` | `ADD rd, rd, rs2` | Soma compacta |  
| `C.LW rd, offset(rs1)` | `LW rd, offset(rs1)` | Load word compacto |  
| `C.SW rs2, offset(rs1)` | `SW rs2, offset(rs1)` | Store word compacto |  
| `C.J offset` | `JAL x0, offset` | Jump relativo |  

---

### **4. Extensão de Ponto Flutuante (F/D)**  
| Instrução | Operação | Descrição |  
|-----------|----------|-----------|  
| `FADD.S rd, rs1, rs2` | rd = rs1 + rs2 | Soma (single-precision) |  
| `FSUB.S rd, rs1, rs2` | rd = rs1 - rs2 | Subtração (single) |  
| `FMUL.S rd, rs1, rs2` | rd = rs1 * rs2 | Multiplicação (single) |  
| `FDIV.S rd, rs1, rs2` | rd = rs1 / rs2 | Divisão (single) |  
| `FADD.D rd, rs1, rs2` | rd = rs1 + rs2 | Soma (double-precision) |  
| `FSQRT.S rd, rs1` | rd = √rs1 | Raiz quadrada |  

---

### **5. Extensão Atômica (A)**  
| Instrução | Operação | Descrição |  
|-----------|----------|-----------|  
| `LR.W rd, (rs1)` | rd = Mem[rs1] | Load-reservado |  
| `SC.W rd, rs2, (rs1)` | Mem[rs1] = rs2; rd = 0/1 | Store-condicional |  
| `AMOADD.W rd, rs2, (rs1)` | Mem[rs1] += rs2; rd = antigo valor | Atomic add |  

---

### **6. Extensão Vetorial (V)**  
| Instrução | Operação | Descrição |  
|-----------|----------|-----------|  
| `VADD.VV vd, vs2, vs1` | vd[i] = vs2[i] + vs1[i] | Soma vetorial |  
| `VMUL.VX vd, vs2, rs1` | vd[i] = vs2[i] * x[rs1] | Multiplicação vetor-escalar |  

---

### **7. Instruções de Sistema e Chamadas de Ambiente**  
| Instrução | Descrição |  
|-----------|-----------|  
| `ECALL` | Chamada de sistema |  
| `EBREAK` | Ponto de depuração |  
| `CSRRW rd, csr, rs1` | Lê/escreve CSR |  

---

### **8. Resumo das Extensões**  
| Extensão | Instruções Adicionadas |  
|----------|------------------------|  
| **M** | `MUL`, `DIV`, `REM` |  
| **A** | `LR.W`, `SC.W`, `AMOADD` |  
| **F/D** | `FADD.S`, `FMUL.D`, `FSQRT` |  
| **C** | `C.ADD`, `C.LW`, `C.J` |  
| **B** | `CLZ`, `CPOP` (bit manipulation) |  
| **V** | `VADD`, `VMUL` (vetores) |  

---

### **9. Referências Oficiais**  
- **RISC-V ISA Manual**: ([The RISC-V ISA specifications](https://riscv.org/specifications/))  
- **RISC-V Cards**: [(RISC-V Reference)](https://www.cs.sfu.ca/~ashriram/Courses/CS295/assets/notebooks/RISCV/RISCV_CARD.pdf)  

## **Exemplos de Código em RISC-V para Tarefas Comuns**  

Este documento apresenta exemplos práticos de programas em **RISC-V Assembly** para operações básicas, estruturas de controle, acesso à memória e chamadas de sistema.  

---

### **1. Hello World (Chamada de Sistema para Escrita)**  
```assembly
.data
msg: .asciz "Hello, RISC-V!\n"  # String terminada em null

.text
.global _start
_start:
    # Chamada syscall 'write' (64)
    li a7, 64         # Código da syscall 'write'
    li a0, 1           # File descriptor (1 = stdout)
    la a1, msg         # Endereço da string
    li a2, 14          # Tamanho da string
    ecall              # Executa a syscall

    # Chamada syscall 'exit' (93)
    li a7, 93          # Código da syscall 'exit'
    li a0, 0           # Status 0 (sucesso)
    ecall
```
**Explicação**:  
- Usa a syscall `write` para imprimir uma string no console.  
- `a7` armazena o número da syscall, `a0` o file descriptor, `a1` o buffer, e `a2` o tamanho.  

---

### **2. Soma de Dois Números**  
```assembly
.text
.global _start
_start:
    li a0, 5           # Carrega o primeiro valor (5)
    li a1, 3           # Carrega o segundo valor (3)
    add a2, a0, a1     # a2 = a0 + a1

    # (Para debug: o resultado está em a2)
    # Para imprimir, seria necessário converter para string.
```
**Explicação**:  
- Usa `ADD` para somar dois valores imediatos.  

---

### **3. Loop (Contagem de 1 a 10)**  
```assembly
.text
.global _start
_start:
    li t0, 0           # Contador (inicia em 0)
    li t1, 10          # Valor máximo

loop:
    addi t0, t0, 1     # Incrementa contador
    blt t0, t1, loop   # Se t0 < 10, repete

    # Ao sair, t0 = 10
```
**Explicação**:  
- `BLT` (Branch if Less Than) controla o loop.  

---

### **4. Acesso à Memória (Array de Inteiros)**  
```assembly
.data
array: .word 10, 20, 30, 40  # Array de 4 words (32 bits)

.text
.global _start
_start:
    la t0, array       # Carrega endereço do array
    lw t1, 0(t0)       # t1 = array[0] (10)
    lw t2, 4(t0)       # t2 = array[1] (20)
    add t3, t1, t2     # t3 = 10 + 20 = 30

    # Armazena o resultado em array[3]
    sw t3, 12(t0)      # array[3] = 30
```
**Explicação**:  
- `LW` (Load Word) e `SW` (Store Word) acessam memória com offset.  

---

### **5. Chamada de Função (Fibonacci Recursivo)**  
```assembly
.text
.global _start
_start:
    li a0, 5           # Calcula fib(5)
    jal ra, fib        # Chama a função
    j end              # Termina o programa

fib:
    addi sp, sp, -8    # Aloca espaço na stack
    sw ra, 4(sp)       # Salva o endereço de retorno
    sw a0, 0(sp)       # Salva n

    li t0, 1
    ble a0, t0, base_case  # Se n <= 1, retorna n

    addi a0, a0, -1    # n-1
    jal ra, fib        # fib(n-1)
    add t1, zero, a0   # Salva resultado em t1

    lw a0, 0(sp)       # Recupera n
    addi a0, a0, -2    # n-2
    jal ra, fib        # fib(n-2)
    add a0, t1, a0     # a0 = fib(n-1) + fib(n-2)

    j return

base_case:
    # Retorna a0 (n)

return:
    lw ra, 4(sp)       # Restaura ra
    addi sp, sp, 8     # Libera stack
    ret                # Retorna (jalr zero, ra, 0)

end:
    li a7, 93          # Syscall exit
    li a0, 0
    ecall
```
**Explicação**:  
- Usa a stack para salvar `ra` (return address) e argumentos.  
- `JAL` salva o endereço de retorno em `ra`.  

---

### **6. Operações com Ponto Flutuante (Extensão F)**  
```assembly
.text
.global _start
_start:
    # Carrega valores float (precisão simples)
    li t0, 0x40490FDB  # 3.14159 em IEEE 754 (32 bits)
    fmv.w.x f0, t0     # Move para registrador float f0
    li t1, 0x40000000  # 2.0
    fmv.w.x f1, t1

    # Operações
    fadd.s f2, f0, f1  # f2 = 3.14159 + 2.0 = 5.14159
    fmul.s f3, f0, f1  # f3 = 3.14159 * 2.0 = 6.28318
```
**Explicação**:  
- `fmv.w.x` move dados inteiros para registradores float.  
- `fadd.s` e `fmul.s` operam em single-precision (32 bits).  

---

### **7. Manipulação de Strings (Comparação strcmp)**  
```assembly
.data
str1: .asciz "RISC-V"
str2: .asciz "RISC-V"

.text
.global _start
_start:
    la a0, str1        # Endereço de str1
    la a1, str2        # Endereço de str2

strcmp_loop:
    lb t0, 0(a0)       # Carrega byte de str1
    lb t1, 0(a1)       # Carrega byte de str2
    bne t0, t1, not_equal
    beqz t0, equal     # Se chegou ao null terminator
    addi a0, a0, 1     # Próximo byte
    addi a1, a1, 1
    j strcmp_loop

equal:
    li a0, 1           # Strings iguais (retorna 1)
    j end

not_equal:
    li a0, 0           # Strings diferentes (retorna 0)

end:
    li a7, 93          # Syscall exit
    ecall
```
**Explicação**:  
- `LB` (Load Byte) lê caracteres individualmente.  
- `BEQZ` verifica o terminador nulo (`\0`).  

---

### **8. Exemplo com Extensão Compacta (C)**  
```assembly
.text
.global _start
_start:
    c.li a0, 5        # a0 = 5 (instrução compacta)
    c.li a1, 3
    c.add a2, a0, a1  # a2 = a0 + a1 (compacto)
```
**Explicação**:  
- Instruções de 16 bits economizam espaço em código.  

---

### **9. Referências**  
- **Simulador RISC-V**: [RARS](https://github.com/TheThirdOne/rars)
- **GNU Toolchain**: [riscv-gnu-toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain)
- **Exemplos Avançados**: [RISC-V Assembly Programming](https://riscv-programming.org)

Estes exemplos cobrem tarefas essenciais em RISC-V. Para projetos reais, adapte conforme a extensão de instruções suportada pelo seu hardware (ex: RV32IMAC, RV64GC).

## **Referência de Opcodes para Instruções RISC-V**  

Esta tabela lista os **opcodes** (códigos de operação) das principais instruções RISC-V, incluindo o conjunto base (**RV32I/RV64I**) e extensões (**M, A, F, D, C, B**).  

---

### **1. Formato das Instruções RISC-V**  
Todas as instruções em RISC-V têm **32 bits** (ou 16 bits, se usando a extensão **C**). A estrutura geral é:  

| Bits | Campo | Descrição |  
|------|-------|-----------|  
| 31–25 | `funct7` | Função adicional para operações |  
| 24–20 | `rs2` | Registrador fonte 2 |  
| 19–15 | `rs1` | Registrador fonte 1 |  
| 14–12 | `funct3` | Sub-tipo da operação |  
| 11–7 | `rd` | Registrador destino |  
| 6–0 | `opcode` | Código da operação principal |  

---

### **2. Opcodes das Instruções Base (RV32I/RV64I)**  

#### **2.1 Instruções Aritméticas/Lógicas**  
| Instrução | Opcode (hex) | `funct3` | `funct7` | Tipo |  
|-----------|-------------|---------|---------|------|  
| `ADD`    | `0x33`      | `0x0`   | `0x00`  | R |  
| `SUB`    | `0x33`      | `0x0`   | `0x20`  | R |  
| `ADDI`   | `0x13`      | `0x0`   | –       | I |  
| `AND`    | `0x33`      | `0x7`   | `0x00`  | R |  
| `OR`     | `0x33`      | `0x6`   | `0x00`  | R |  
| `XOR`    | `0x33`      | `0x4`   | `0x00`  | R |  
| `ANDI`   | `0x13`      | `0x7`   | –       | I |  
| `ORI`    | `0x13`      | `0x6`   | –       | I |  
| `XORI`   | `0x13`      | `0x4`   | –       | I |  

#### **2.2 Shifts**  
| Instrução | Opcode | `funct3` | `funct7` | Tipo |  
|-----------|--------|---------|---------|------|  
| `SLL`    | `0x33` | `0x1`   | `0x00`  | R |  
| `SRL`    | `0x33` | `0x5`   | `0x00`  | R |  
| `SRA`    | `0x33` | `0x5`   | `0x20`  | R |  
| `SLLI`   | `0x13` | `0x1`   | `0x00`  | I |  
| `SRLI`   | `0x13` | `0x5`   | `0x00`  | I |  
| `SRAI`   | `0x13` | `0x5`   | `0x20`  | I |  

#### **2.3 Load/Store**  
| Instrução | Opcode | `funct3` | Tipo |  
|-----------|--------|---------|------|  
| `LW`     | `0x03` | `0x2`   | I |  
| `LD`     | `0x03` | `0x3`   | I |  
| `SW`     | `0x23` | `0x2`   | S |  
| `SD`     | `0x23` | `0x3`   | S |  

#### **2.4 Branches**  
| Instrução | Opcode | `funct3` | Tipo |  
|-----------|--------|---------|------|  
| `BEQ`    | `0x63` | `0x0`   | B |  
| `BNE`    | `0x63` | `0x1`   | B |  
| `BLT`    | `0x63` | `0x4`   | B |  
| `BGE`    | `0x63` | `0x5`   | B |  
| `BLTU`   | `0x63` | `0x6`   | B |  
| `BGEU`   | `0x63` | `0x7`   | B |  

#### **2.5 Jump e Chamadas**  
| Instrução | Opcode | `funct3` | Tipo |  
|-----------|--------|---------|------|  
| `JAL`    | `0x6F` | –       | J |  
| `JALR`   | `0x67` | `0x0`   | I |  

#### **2.6 Constantes**  
| Instrução | Opcode | Tipo |  
|-----------|--------|------|  
| `LUI`    | `0x37` | U |  
| `AUIPC`  | `0x17` | U |  

---

### **3. Extensão de Multiplicação/Divisão (M)**  
| Instrução | Opcode | `funct3` | `funct7` | Tipo |  
|-----------|--------|---------|---------|------|  
| `MUL`    | `0x33` | `0x0`   | `0x01`  | R |  
| `MULH`   | `0x33` | `0x1`   | `0x01`  | R |  
| `MULHU`  | `0x33` | `0x3`   | `0x01`  | R |  
| `DIV`    | `0x33` | `0x4`   | `0x01`  | R |  
| `DIVU`   | `0x33` | `0x5`   | `0x01`  | R |  
| `REM`    | `0x33` | `0x6`   | `0x01`  | R |  
| `REMU`   | `0x33` | `0x7`   | `0x01`  | R |  

---

### **4. Extensão de Ponto Flutuante (F/D)**  
| Instrução | Opcode | `funct3` | `funct7` | Tipo |  
|-----------|--------|---------|---------|------|  
| `FADD.S` | `0x53` | `0x7`   | `0x00`  | R |  
| `FSUB.S` | `0x53` | `0x7`   | `0x04`  | R |  
| `FMUL.S` | `0x53` | `0x7`   | `0x08`  | R |  
| `FDIV.S` | `0x53` | `0x7`   | `0x0C`  | R |  
| `FADD.D` | `0x53` | `0x1`   | `0x00`  | R |  

---

### **5. Extensão Atômica (A)**  
| Instrução | Opcode | `funct3` | `funct5` | Tipo |  
|-----------|--------|---------|---------|------|  
| `LR.W`   | `0x2F` | `0x2`   | `0x10`  | R |  
| `SC.W`   | `0x2F` | `0x2`   | `0x18`  | R |  
| `AMOADD.W` | `0x2F` | `0x2` | `0x00` | R |  

---

### **6. Extensão Compacta (C)**  
Instruções de 16 bits com opcodes especiais:  
| Instrução | Opcode (hex) |  
|-----------|-------------|  
| `C.ADD`  | `0x9` |  
| `C.LW`   | `0x2` |  
| `C.SW`   | `0x6` |  
| `C.J`    | `0x1` |  

---

### **7. Chamadas de Sistema**  
| Instrução | Opcode |  
|-----------|--------|  
| `ECALL`  | `0x73` |  
| `EBREAK` | `0x73` |  

---

### **8. Tabela Resumo de Opcodes Principais**  
| Categoria | Opcode (hex) |  
|-----------|-------------|  
| **Aritméticas** | `0x13` (I), `0x33` (R) |  
| **Load/Store** | `0x03` (I), `0x23` (S) |  
| **Branch** | `0x63` (B) |  
| **Jump** | `0x6F` (J), `0x67` (I) |  
| **Sistema** | `0x73` |  

---

### **9. Referências**  
- **RISC-V ISA Manual** ([riscv.org/specifications](https://riscv.org/specifications/))  
- **Lista Completa de Opcodes**: [RISC-V Card](https://inst.eecs.berkeley.edu/~cs61c/fa18/img/riscvcard.pdf)  

Esta referência cobre os opcodes essenciais para programação em RISC-V. Para detalhes completos, consulte o manual oficial.

## **Exemplos em RISC-V para ESP32-C3**  

O **ESP32-C3** é um SoC baseado em RISC-V com suporte para Wi-Fi, Bluetooth, GPIOs, e periféricos comuns. Abaixo estão exemplos práticos de como controlar dispositivos como LCD, teclado matricial, buzzer, sensores, SD Card, Wi-Fi e Bluetooth usando **RISC-V Assembly** e **C com o ESP-IDF**.  

---

### **1. Configuração Inicial (GPIO e UART)**  

#### **1.1 Piscar LED (GPIO)**  
**Código em C (ESP-IDF):**  
```c
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_GPIO 2

void app_main() {
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    while (1) {
        gpio_set_level(LED_GPIO, 1);  // Liga LED
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(LED_GPIO, 0);  // Desliga LED
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
```
**Explicação:**  
- Configura o pino `GPIO2` como saída e alterna seu estado a cada 1 segundo.  

---

### **2. Display LCD (I2C ou GPIO Direto)**  

#### **2.1 LCD 16x2 via I2C**  
**Código em C (ESP-IDF):**  
```c
#include "driver/i2c.h"
#include "esp_log.h"

#define I2C_MASTER_SCL_IO 4
#define I2C_MASTER_SDA_IO 5
#define LCD_ADDR 0x27

void lcd_send_cmd(uint8_t cmd) {
    uint8_t data[4] = {cmd | 0x04, cmd & ~0x04};
    i2c_master_write_to_device(I2C_NUM_0, LCD_ADDR, data, 2, 1000 / portTICK_PERIOD_MS);
}

void app_main() {
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000,
    };
    i2c_param_config(I2C_NUM_0, &conf);
    i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);

    lcd_send_cmd(0x33);  // Inicialização
    lcd_send_cmd(0x32);
    lcd_send_cmd(0x28);  // Modo 4 bits, 2 linhas
    lcd_send_cmd(0x0C);  // LCD ligado, cursor off
    lcd_send_cmd(0x01);  // Limpa display
    lcd_send_cmd(0x80);  // Posiciona cursor na linha 1
}
```
**Explicação:**  
- Usa **I2C** para enviar comandos a um **LCD 16x2** com controlador PCF8574.  

---

### **3. Teclado Matricial (GPIO Scanning)**  

#### **3.1 Leitura de Teclado 4x4**  
**Código em C (ESP-IDF):**  
```c
#define ROWS 4
#define COLS 4

const uint8_t row_pins[ROWS] = {12, 13, 14, 15};
const uint8_t col_pins[COLS] = {16, 17, 18, 19};
const char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

char read_keypad() {
    for (int c = 0; c < COLS; c++) {
        gpio_set_level(col_pins[c], 0);
        for (int r = 0; r < ROWS; r++) {
            if (gpio_get_level(row_pins[r]) == 0) {
                vTaskDelay(50 / portTICK_PERIOD_MS);  // Debounce
                return keys[r][c];
            }
        }
        gpio_set_level(col_pins[c], 1);
    }
    return '\0';
}
```
**Explicação:**  
- Varre as linhas e colunas para detectar teclas pressionadas.  

---

### **4. Buzzer (PWM)**  

#### **4.1 Gerar Tom com PWM**  
**Código em C (ESP-IDF):**  
```c
#include "driver/ledc.h"

#define BUZZER_PIN 8
#define PWM_FREQ 2000  // 2 kHz

void app_main() {
    ledc_timer_config_t timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_8_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = PWM_FREQ,
    };
    ledc_timer_config(&timer);

    ledc_channel_config_t channel = {
        .gpio_num = BUZZER_PIN,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_0,
        .duty = 128,  // 50% duty cycle
    };
    ledc_channel_config(&channel);

    while (1) {
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 128);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
```
**Explicação:**  
- Usa **LEDC (PWM)** para gerar um tom em um buzzer passivo.  

---

### **5. Sensores (ADC e I2C/SPI)**  

#### **5.1 Leitura de Sensor de Temperatura (DS18B20 - OneWire)**  
**Código em C (ESP-IDF):**  
```c
#include "driver/gpio.h"
#include "ds18b20.h"

#define DS18B20_GPIO 10

void app_main() {
    float temp;
    ds18b20_init(DS18B20_GPIO);
    
    while (1) {
        ds18b20_read_temp(DS18B20_GPIO, &temp);
        printf("Temperatura: %.2f °C\n", temp);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}
```
**Explicação:**  
- Usa o protocolo **OneWire** para ler temperatura do **DS18B20**.  

---

### **6. Acesso a SD Card (SPI)**  

#### **6.1 Escrever em Arquivo no SD Card**  
**Código em C (ESP-IDF):**  
```c
#include "sdmmc_cmd.h"
#include "driver/sdmmc_host.h"

void app_main() {
    sdmmc_host_t host = SDMMC_HOST_DEFAULT();
    sdmmc_slot_config_t slot = SDMMC_SLOT_CONFIG_DEFAULT();
    esp_vfs_fat_sdmmc_mount_config_t mount = {
        .format_if_mount_failed = true,
        .max_files = 5,
    };
    sdmmc_card_t *card;
    esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot, &mount, &card);

    FILE *f = fopen("/sdcard/teste.txt", "w");
    fprintf(f, "Hello, SD Card!");
    fclose(f);

    esp_vfs_fat_sdmmc_unmount();
}
```
**Explicação:**  
- Monta o sistema de arquivos FAT e escreve em um arquivo.  

---

### **7. Comunicação Wi-Fi (TCP/IP)**  

#### **7.1 Conectar a Wi-Fi e Enviar Requisição HTTP**  
**Código em C (ESP-IDF):**  
```c
#include "esp_wifi.h"
#include "esp_http_client.h"

void app_main() {
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    esp_wifi_set_mode(WIFI_MODE_STA);
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = "MinhaRede",
            .password = "Senha123",
        },
    };
    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);
    esp_wifi_start();
    esp_wifi_connect();

    esp_http_client_config_t http = {
        .url = "http://example.com/api",
        .method = HTTP_METHOD_GET,
    };
    esp_http_client_handle_t client = esp_http_client_init(&http);
    esp_http_client_perform(client);
    esp_http_client_cleanup(client);
}
```
**Explicação:**  
- Conecta-se a uma rede Wi-Fi e faz uma requisição HTTP GET.  

---

### **8. Comunicação Bluetooth (BLE)**  

#### **8.1 Enviar Dados via BLE**  
**Código em C (ESP-IDF):**  
```c
#include "esp_bt.h"
#include "esp_gap_ble_api.h"

void app_main() {
    esp_bt_controller_config_t cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    esp_bt_controller_init(&cfg);
    esp_bt_controller_enable(ESP_BT_MODE_BLE);

    esp_ble_gap_config_adv_data(&(esp_ble_adv_data_t){
        .set_scan_rsp = false,
        .include_name = true,
        .include_txpower = true,
    });

    esp_ble_gap_start_advertising(&(esp_ble_adv_params_t){
        .adv_int_min = 0x20,
        .adv_int_max = 0x40,
        .adv_type = ADV_TYPE_IND,
        .channel_map = ADV_CHNL_ALL,
    });
}
```
**Explicação:**  
- Configura o ESP32-C3 como um dispositivo BLE e inicia advertising.  

---

### **9. Referências**  
- **[ESP-IDF Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/)**  
- **[RISC-V Assembly for ESP32-C3](https://github.com/espressif/esp-riscv)**  

Estes exemplos cobrem aplicações comuns no ESP32-C3. Para projetos avançados, consulte a documentação oficial. 🚀

## **Funcionamento do Bootloader do ESP32-C3**

O **bootloader** do ESP32-C3 é um pequeno programa executado na inicialização (*boot*) que prepara o sistema, carrega a aplicação principal e pode gerenciar atualizações de firmware (*OTA*). Ele é crucial para o funcionamento correto do chip e suporta múltiplos estágios de inicialização.

---

### **1. Arquitetura do Bootloader (RISC-V)**
O ESP32-C3 é baseado em um núcleo **RISC-V de 32 bits**, e seu bootloader segue um fluxo estruturado:

1. **ROM Bootloader (Primeiro Estágio - Hardcoded na ROM)**  
   - Executado automaticamente ao ligar o chip (*power-on reset*).  
   - Responsável por:  
     - Inicializar o clock e configurações básicas do SoC.  
     - Decidir o **modo de boot** (via estados dos pinos GPIO).  
     - Carregar o **segundo estágio do bootloader** (na flash) ou entrar em modo de download via UART.  

2. **Second-Stage Bootloader (Na Flash - Personalizável)**  
   - Armazenado na **partição `bootloader`** da memória flash.  
   - Responsável por:  
     - Configurar periféricos críticos (SPI Flash, PSRAM, etc.).  
     - Verificar e carregar a **aplicação principal** (firmware).  
     - Suportar **OTA (Atualização Over-The-Air)**.  

---

### **2. Fluxo de Boot Completo**
| Etapa | Ação |  
|-------|------|  
| **1. Reset** | Chip liga ou é reiniciado. |  
| **2. ROM Bootloader** |   - Verifica os pinos `GPIO9` (SPI_CS) e `GPIO8` (SPI_MISO) para definir o modo de boot.<br> - Se `GPIO9 = LOW`, entra em modo de download via UART.<br> - Se `GPIO9 = HIGH`, carrega o bootloader da flash. |  
| **3. Second-Stage Bootloader** |   - Lê a tabela de partições da flash.<br> - Carrega o firmware da partição `app` (ou `factory`).<br> - Pode verificar assinaturas de segurança (se habilitado). |  
| **4. Aplicação Principal** | Execução do firmware do usuário. |  

---

### **3. Modos de Boot do ESP32-C3**
O comportamento do bootloader é definido pelos **pinos de boot**:

| Pino | Função | Estado para Modo Normal | Estado para Modo Download |  
|------|--------|-------------------------|---------------------------|  
| **GPIO9** | Boot Mode Select | `HIGH` (1) | `LOW` (0) |  
| **GPIO8** | Boot Mode Confirm | Ignorado | Deve estar `HIGH` (1) |  

- **Modo Normal**:  
  - `GPIO9 = HIGH` → Boot da flash.  
- **Modo Download (Para Flashear Firmware)**:  
  - `GPIO9 = LOW` + `GPIO8 = HIGH` → Comunicação via UART com `esptool.py`.  

---

### **4. Partições da Flash**
O ESP32-C3 usa uma **tabela de partições** (geralmente em `partitions.csv`) para organizar a flash:  

| Partição | Função |  
|----------|--------|  
| **bootloader** | Contém o second-stage bootloader. |  
| **partition_table** | Define as partições (app, OTA, dados, etc.). |  
| **factory** | Firmware padrão (opcional). |  
| **ota_0 / ota_1** | Partições para atualização OTA. |  
| **nvs** | Armazena configurações não voláteis. |  
| **spiffs / fatfs** | Sistema de arquivos (opcional). |  

Exemplo de `partitions.csv`:
```
# Name,   Type, SubType, Offset,  Size
bootloader,  app,  boot,  0x1000,  0x7000
partition_table, data,  nvs,    0x8000,  0x1000
factory,  app,  factory, 0x10000, 1M
ota_0,    app,  ota_0,   ,        1M
ota_1,    app,  ota_1,   ,        1M
nvs,      data,  nvs,     ,        0x4000
```

---

### **5. Secure Boot e Verificação de Firmware**
O ESP32-C3 suporta:  
- **Secure Boot V2**:  
  - Verifica assinatura digital do firmware durante o boot.  
  - Evita execução de código malicioso.  
- **Flash Encryption**:  
  - Criptografa o conteúdo da flash para proteger dados sensíveis.  

---

### **6. Personalizando o Bootloader**
O **second-stage bootloader** pode ser modificado no ESP-IDF:  
```c
// Exemplo de hook no bootloader (em C)
void __attribute__((weak)) bootloader_custom_start(void) {
    printf("Bootloader personalizado!\n");
}
```
- Compilado em `components/bootloader`.  
- Pode adicionar logs, atrasos ou verificações extras.  

---

### **7. Ferramentas para Gerenciamento do Bootloader**
- **esptool.py**:  
  - Usado para flashear o bootloader e firmware:  
  ```bash
  esptool.py --chip esp32c3 write_flash 0x0 bootloader.bin
  ```
- **ESP-IDF Build System**:  
  - Gera automaticamente o `bootloader.bin` ao compilar.  

---

### **8. Problemas Comuns e Soluções**
| Problema | Causa | Solução |  
|----------|-------|---------|  
| **Chip não boota** | Pinos de boot incorretos | Verificar `GPIO9` e `GPIO8`. |  
| **Falha na verificação** | Secure Boot ativo sem assinatura | Desativar Secure Boot ou assinar o firmware. |  
| **Erro "Invalid image length"** | Partição corrompida | Refazer flash com `esptool.py --erase-all`. |  

---

### **9. Referências**
- [Documentação Oficial do Bootloader (ESP-IDF)](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/api-reference/system/bootloader.html)  
- [Guia de Particionamento](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/api-guides/partition-tables.html)  
- [Secure Boot V2](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/security/secure-boot-v2.html)  

O bootloader do ESP32-C3 é altamente configurável e essencial para operações seguras e estáveis. Se precisar de mais detalhes, consulte a documentação da Espressif! 🚀

## **Tradução de Estruturas C para RISC-V Assembly**

Abaixo apresento a equivalência entre construções básicas da linguagem C e sua implementação em RISC-V Assembly, com exemplos funcionais que podem ser compilados diretamente:

### **1. Declaração de Variáveis**

#### **Código C:**
```c
int a = 10;
int b = 20;
int c;
```

#### **RISC-V Assembly:**
```assembly
.data
a: .word 10        # int a = 10
b: .word 20        # int b = 20
c: .word 0         # int c = 0

.text
.globl main
main:
    # Acesso às variáveis
    la t0, a       # Carrega endereço de 'a' em t0
    lw t1, 0(t0)   # t1 = valor de a (10)
    la t0, b
    lw t2, 0(t0)   # t2 = valor de b (20)
```

### **2. Estruturas Condicionais (if-else)**

#### **Código C:**
```c
if (a > b) {
    c = a;
} else {
    c = b;
}
```

#### **RISC-V Assembly:**
```assembly
    lw t1, a       # t1 = a
    lw t2, b       # t2 = b
    ble t1, t2, else_label  # if (a <= b) jump else
    sw t1, c       # c = a
    j end_if
else_label:
    sw t2, c       # c = b
end_if:
```

### **3. Laços de Repetição (for/while)**

#### **Código C (for):**
```c
for (int i = 0; i < 10; i++) {
    c += i;
}
```

#### **RISC-V Assembly:**
```assembly
    li t0, 0       # i = 0
    li t3, 10      # limite = 10
    lw t4, c       # Carrega valor de c
loop:
    bge t0, t3, end_loop  # if i >= 10, exit
    add t4, t4, t0 # c += i
    addi t0, t0, 1 # i++
    j loop
end_loop:
    sw t4, c       # Armazena novo valor em c
```

#### **Código C (while):**
```c
while (a < 100) {
    a *= 2;
}
```

#### **RISC-V Assembly:**
```assembly
    lw t1, a       # t1 = a
    li t2, 100     # t2 = 100
while_loop:
    bge t1, t2, end_while
    slli t1, t1, 1 # a *= 2 (shift left = multiplicação por 2)
    j while_loop
end_while:
    sw t1, a       # Atualiza valor na memória
```

### **4. Funções**

#### **Código C:**
```c
int soma(int x, int y) {
    return x + y;
}

int main() {
    int resultado = soma(5, 3);
}
```

#### **RISC-V Assembly:**
```assembly
.text
.globl main

soma:
    add a0, a0, a1  # a0 = x + y (a0 é o registrador de retorno)
    ret             # jalr zero, ra, 0

main:
    li a0, 5        # Primeiro argumento (x)
    li a1, 3        # Segundo argumento (y)
    jal ra, soma    # Chama função
    # Resultado está em a0
    sw a0, resultado, t0  # Armazena resultado

.data
resultado: .word 0
```

### **5. Arrays**

#### **Código C:**
```c
int arr[5] = {1, 2, 3, 4, 5};
int sum = 0;
for (int i = 0; i < 5; i++) {
    sum += arr[i];
}
```

#### **RISC-V Assembly:**
```assembly
.data
arr: .word 1, 2, 3, 4, 5
sum: .word 0

.text
.globl main
main:
    la t0, arr      # Endereço base do array
    li t1, 0        # i = 0
    li t2, 5        # tamanho = 5
    li t3, 0        # sum = 0
loop:
    bge t1, t2, end_loop
    slli t4, t1, 2  # i * 4 (offset em bytes)
    add t5, t0, t4  # endereço de arr[i]
    lw t6, 0(t5)    # t6 = arr[i]
    add t3, t3, t6  # sum += arr[i]
    addi t1, t1, 1  # i++
    j loop
end_loop:
    sw t3, sum, t0  # Armazena resultado
```

### **6. Otimizações Importantes**

1. **Uso de Registradores Temporários**:
   - `t0-t6` para cálculos intermediários
   - `a0-a7` para argumentos de funções
   - `s0-s11` para variáveis preservadas entre chamadas

2. **Acesso Eficiente à Memória**:
   - Sempre alinhar dados em palavras (4 bytes)
   - Usar `la` + `lw/sw` em vez de múltiplos acessos absolutos

3. **Pilha para Chamadas Aninhadas**:
```assembly
func:
    addi sp, sp, -16   # Aloca espaço na pilha
    sw ra, 12(sp)      # Salva endereço de retorno
    # ... código ...
    lw ra, 12(sp)      # Restaura ra
    addi sp, sp, 16    # Libera pilha
    ret
```

### **Ferramentas Recomendadas**

1. **Compilador**: `riscv64-unknown-elf-gcc`
   ```bash
   riscv64-unknown-elf-gcc -march=rv32im -mabi=ilp32 -o prog prog.s
   ```

2. **Simulador**: `spike` + `pk`
   ```bash
   spike pk prog
   ```

3. **Debugger**: `gdb-multiarch`
   ```bash
   riscv64-unknown-elf-gdb prog
   ```

Estes exemplos cobrem as construções básicas do C com equivalência direta em RISC-V. Para casos mais complexos (structs, ponteiros, etc.), são necessárias estratégias adicionais de manipulação de memória.
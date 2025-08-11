# Guia Avançado de Programação para Cardputer

## Parte 1: Exemplos Comentados

### Exemplo 1: Soma de dois números com entrada pelo teclado

```asm
; Programa para somar dois números digitados e mostrar resultado

START:
    IN          ; Lê primeiro número
    STA 0x0A    ; Armazena em 0x0A
    IN          ; Lê segundo número
    STA 0x0B    ; Armazena em 0x0B
    LDA 0x0A    ; Carrega primeiro número
    ADD 0x0B    ; Soma segundo número
    STA 0x0C    ; Armazena resultado
    LDA 0x0C    ; Prepara saída
    OUT         ; Mostra resultado
    JMP START   ; Repete
```

---

### Exemplo 2: Contador de 0 a 9 com saída na tela

```asm
START:
    LDA 0x00    ; Zera contador
    STA 0x0D

LOOP:
    LDA 0x0D    ; Carrega contador
    OUT         ; Exibe contador
    ADD 0x01    ; Incrementa contador
    STA 0x0D
    SUB 0x0A    ; Subtrai 10
    JZ END      ; Se zero, fim
    JMP LOOP

END:
    HALT        ; Para execução
```

---

### Exemplo 3: Leitura e escrita básica no SD Card

```asm
    LDA 0x00    ; Endereço inicial SD
    WR_SD       ; Escreve acumulador no SD
    RD_SD       ; Lê byte do SD para acumulador
    OUT         ; Mostra byte lido
    HALT
```

---

## Parte 2: Simulador Básico em Python

Este simulador simples interpreta instruções do Cardputer, permitindo testar pequenos programas sem hardware.

```python
class CardputerSim:
    def __init__(self):
        self.memory = [0]*256
        self.ac = 0          # Acumulador
        self.pc = 0          # Program Counter
        self.running = True

    def load_program(self, program):
        for i, byte in enumerate(program):
            self.memory[i] = byte

    def run(self):
        while self.running:
            instr = self.memory[self.pc]
            opcode = instr >> 4
            addr = instr & 0x0F
            self.pc += 1

            if opcode == 0x1:       # LDA
                self.ac = self.memory[addr]
            elif opcode == 0x2:     # STA
                self.memory[addr] = self.ac
            elif opcode == 0x3:     # ADD
                self.ac += self.memory[addr]
                self.ac &= 0xFF    # Overflow 8-bit
            elif opcode == 0x4:     # SUB
                self.ac -= self.memory[addr]
                self.ac &= 0xFF
            elif opcode == 0x5:     # JMP
                self.pc = addr
            elif opcode == 0x6:     # JZ
                if self.ac == 0:
                    self.pc = addr
            elif opcode == 0x7:     # JNZ
                if self.ac != 0:
                    self.pc = addr
            elif instr == 0x80:     # IN
                val = input("Enter number (0-255): ")
                try:
                    self.ac = int(val) & 0xFF
                except:
                    self.ac = 0
            elif instr == 0x90:     # OUT
                print(f"Output: {self.ac}")
            elif instr == 0xD0:     # HALT
                print("Execution halted.")
                self.running = False
            else:
                print(f"Unknown instruction: {instr:02X}")
                self.running = False

if __name__ == "__main__":
    # Exemplo: programa soma 2 números e exibe resultado
    prog = [
        0x80,       # IN
        0x2A,       # STA 0x0A
        0x80,       # IN
        0x2B,       # STA 0x0B
        0x1A,       # LDA 0x0A
        0x3B,       # ADD 0x0B
        0x2C,       # STA 0x0C
        0x1C,       # LDA 0x0C
        0x90,       # OUT
        0x50        # JMP 0x00
    ]

    sim = CardputerSim()
    sim.load_program(prog)
    sim.run()
```

---

## Parte 3: Detalhes sobre uso do SD Card

* O cartão SD é acessado com comandos `RD_SD` e `WR_SD`.
* Endereço para leitura/gravação deve ser gerenciado em memória.
* Operações podem ser lentas, importante usar rotinas para controle e confirmação.
* Nem todos os modelos suportam SD card; verifique seu manual.

---

## Parte 4: Dicas para Programação

* Use variáveis em endereços fixos para organizar dados.
* Controle fluxo com saltos condicionais para criar loops e decisões.
* Teste programas no simulador antes de rodar no hardware.
* Documente seu código com comentários para facilitar manutenção.

---


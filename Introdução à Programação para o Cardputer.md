# Introdução à Programação para o Cardputer

## 1. Introdução

O Cardputer foi projetado para ensinar os conceitos básicos de computação e programação. Seu processador simples e conjunto limitado de instruções permitem que o estudante entenda passo a passo como um computador funciona, desde a manipulação de memória até operações aritméticas.

---

## 2. Arquitetura Básica

* Memória limitada, geralmente em torno de 256 a 512 bytes.
* Registradores básicos: acumulador, registrador de instrução, contador de programa.
* Programa carregado em memória RAM.
* Instruções com formato simples, geralmente uma operação seguida de endereço.

---

## 3. Conjunto de Instruções Básico

| Código | Instrução | Descrição                                        |
| ------ | --------- | ------------------------------------------------ |
| 0x1X   | LDA addr  | Carrega no acumulador o valor do endereço `addr` |
| 0x2X   | STA addr  | Armazena acumulador em `addr`                    |
| 0x3X   | ADD addr  | Soma o valor em `addr` ao acumulador             |
| 0x4X   | SUB addr  | Subtrai o valor em `addr` do acumulador          |
| 0x5X   | JMP addr  | Salta para o endereço `addr`                     |
| 0x6X   | JZ addr   | Salta para `addr` se acumulador for zero         |
| 0x7X   | JNZ addr  | Salta para `addr` se acumulador não for zero     |
| 0x80   | IN        | Lê dado do teclado para acumulador               |
| 0x90   | OUT       | Escreve valor do acumulador na tela              |

---

## 4. Formato da Instrução

* 8 bits: 4 bits para o código da operação + 4 bits para o endereço (ou dado imediato).
* Exemplo: `0x1A` pode significar LDA no endereço 0xA.

---

## 5. Escrevendo um Programa Simples

Objetivo: Somar dois números digitados pelo usuário e mostrar o resultado.

```asm
; Endereços de memória
NUM1  EQU 0x0A
NUM2  EQU 0x0B
RESULT EQU 0x0C

START:
    IN          ; Lê primeiro número para acumulador
    STA NUM1    ; Armazena em NUM1
    IN          ; Lê segundo número para acumulador
    STA NUM2    ; Armazena em NUM2
    LDA NUM1    ; Carrega NUM1
    ADD NUM2    ; Soma NUM2
    STA RESULT  ; Armazena resultado
    LDA RESULT  ; Carrega resultado para saída
    OUT         ; Mostra resultado
    JMP START   ; Loop infinito
```

---

## 6. Como carregar e executar

* O programa deve ser escrito em código hexadecimal.
* Usar a interface de entrada do Cardputer para carregar o programa.
* Executar passo a passo para ver o funcionamento.

---


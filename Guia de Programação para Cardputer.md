# Guia de Programação para Cardputer

## 1. Introdução

O Cardputer é um microcomputador educacional simples, ideal para aprender fundamentos de programação em baixo nível. Ele possui:

* CPU simples com conjunto reduzido de instruções.
* Memória RAM limitada.
* Entrada via teclado matricial.
* Saída em tela de texto simples.
* Leitura e gravação via cartão SD (em alguns modelos).

Este tutorial vai te guiar do básico até operações mais avançadas, com exemplos claros.

---

## 2. Arquitetura Básica

| Componente        | Descrição                                                                 |
| ----------------- | ------------------------------------------------------------------------- |
| **Memória RAM**   | 256 a 512 bytes, onde programa e dados ficam                              |
| **Registradores** | Acumulador (AC), Contador de Programa (PC), Registrador de Instrução (IR) |
| **Entrada**       | Teclado matricial                                                         |
| **Saída**         | Tela de texto (LCD ou monitor simples)                                    |
| **Armazenamento** | Cartão SD (opcional)                                                      |

---

## 3. Formato da Instrução

Cada instrução tem 8 bits:

* 4 bits para o código da operação (opcode)
* 4 bits para o endereço da memória ou dado imediato

Exemplo: `0x1A` → opcode `1` (LDA), endereço `0xA`.

---

## 4. Conjunto de Instruções Comuns

| Opcode (hex) | Instrução | Descrição                                           |
| ------------ | --------- | --------------------------------------------------- |
| 1x           | LDA addr  | Carrega acumulador com valor da memória no endereço |
| 2x           | STA addr  | Armazena acumulador na memória no endereço          |
| 3x           | ADD addr  | Soma valor da memória ao acumulador                 |
| 4x           | SUB addr  | Subtrai valor da memória do acumulador              |
| 5x           | JMP addr  | Salta para endereço indicado                        |
| 6x           | JZ addr   | Salta se acumulador for zero                        |
| 7x           | JNZ addr  | Salta se acumulador não for zero                    |
| 80           | IN        | Lê do teclado para acumulador                       |
| 90           | OUT       | Escreve acumulador na tela                          |
| A0           | RD\_SD    | Lê byte do cartão SD para acumulador                |
| B0           | WR\_SD    | Grava acumulador no cartão SD                       |
| C0           | WAIT      | Espera por um ciclo (delay)                         |
| D0           | HALT      | Para execução até reset                             |

---

## 5. Exemplos Práticos

### Exemplo 1: Soma de dois números via teclado

```asm
START:
    IN          ; Lê primeiro número do teclado
    STA 0x0A    ; Armazena em endereço 0x0A
    IN          ; Lê segundo número do teclado
    STA 0x0B    ; Armazena em endereço 0x0B
    LDA 0x0A    ; Carrega primeiro número no acumulador
    ADD 0x0B    ; Soma segundo número ao acumulador
    STA 0x0C    ; Armazena resultado em 0x0C
    LDA 0x0C    ; Carrega resultado para saída
    OUT         ; Mostra resultado na tela
    JMP START   ; Repete o processo
```

---

### Exemplo 2: Loop contando de 0 a 9

```asm
START:
    LDA 0x00    ; Inicializa contador em 0
    STA 0x0D

LOOP:
    LDA 0x0D    ; Carrega contador
    OUT         ; Mostra valor na tela
    ADD 0x01    ; Incrementa contador (+1)
    STA 0x0D    ; Atualiza contador
    SUB 0x0A    ; Subtrai 10 para verificar limite
    JZ END      ; Se zero, termina
    JMP LOOP

END:
    HALT        ; Para execução
```

---

### Exemplo 3: Ler byte do cartão SD e mostrar

```asm
    LDA 0x00    ; Endereço inicial no SD
    WR_SD       ; Comando fictício para preparar leitura
    RD_SD       ; Lê byte do SD para acumulador
    OUT         ; Exibe valor na tela
    HALT
```

*Obs.:* Os comandos `RD_SD` e `WR_SD` dependem do modelo do Cardputer. Consulte o manual para detalhes.

---

## 6. Uso do Teclado

* O comando `IN` aguarda o usuário digitar um número (normalmente de 0 a 9).
* O valor digitado é carregado diretamente no acumulador.
* Pode-se criar rotinas para detectar teclas especiais ou múltiplos dígitos.

---

## 7. Uso da Tela

* O comando `OUT` envia o valor do acumulador para a tela.
* Pode exibir números ou códigos ASCII para caracteres.
* Para criar textos, envie um byte por vez, controlando posições com comandos específicos (se houver suporte).

---

## 8. Uso do Cartão SD (Se disponível)

* Normalmente, o Cardputer pode ler e gravar dados no cartão SD para persistência.
* Os comandos `RD_SD` e `WR_SD` realizam operações básicas.
* Endereçamento e buffers dependem do firmware instalado.
* Utilize rotinas para inicializar e verificar status do cartão.

---

## 9. Dicas Avançadas

* Use endereços fixos para variáveis e buffers.
* Controle o fluxo com saltos condicionais (`JZ`, `JNZ`) para criar estruturas.
* Combine leitura do teclado, cálculo e saída para interatividade.
* Use o `HALT` para economizar energia ou pausar execução.

---

## 10. Como Carregar Programas no Cardputer

* Converta seu código em bytes hexadecimais.
* Use a interface do Cardputer para carregar o programa na memória.
* Execute passo a passo para depurar.

---


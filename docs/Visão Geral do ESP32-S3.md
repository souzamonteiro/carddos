# Visão Geral do ESP32-S3

O ESP32-S3 traz um coprocessador **ULP-RISC-V**, programável em C ou Assembly com o *toolchain* RISC-V padrão ([docs.espressif.com][1], [cdn-learn.adafruit.com][2]). Além disso, inclui o coprocessador **ULP-FSM**, com 4 registradores de 16 bits e um contador (`stage_cnt`) especial para loops ([docs.espressif.com][3], [cdn-learn.adafruit.com][2]).

---

## 1. Assembly RISC-V para ULP-RISC-V

Usa-se o conjunto **RV32IMC**, incluindo multiplicação/divisão e instruções comprimidas (C-extension) ([docs.espressif.com][1]). Aqui estão os blocos essenciais:

### a) Registradores e Instruções Base

* **Registradores**: padrão RISC-V (x0-x31) disponíveis para o ULP-RISC-V.
* **Instruções comuns**:

  * Aritmética: `addi`, `add`, `sub`, `mul`, `div`
  * Carregar/armazenar: `lw`, `sw`, `lb`, `sb`
  * Controle: `beq`, `bne`, `blt`, `bge`
  * Jump: `jal`, `jalr`
  * Comprimidas: `C.*` (ex: `c.addi`) permitem código eficiente ([docs.espressif.com][1]).

### b) Exemplo de sequência (acionamento de GPIO com atraso)

```asm
.section .text
.global _start
_start:
    movi a2, 0x3FF44000      # endereço base do GPIO
    movi a3, 1 << 15         # máscara do pino 15
s32i a3, a2, 0x4            # set bit (GPIO OUT)
call0 delay
#...
j loop
delay:
    movi a1, 0x3FFFFF
delay_loop:
    addi a1, a1, -1
    bnez a1, delay_loop
    ret
```

Esse exemplo foi retirado de uma discussão real de implementação em Assembly para ESP32-S3 ([Stack Overflow][4]).

---

## 2. Instruções ULP-FSM (Finite State Machine)

O ULP-FSM tem recursos mais restritos, mas úteis em casos críticos de baixo consumo:

* **Registradores**: R0, R1, R2, R3 (16 bits) + `stage_cnt` (contador de iterações) ([docs.espressif.com][3]).
* Ideal para leituras de sensores e wake-up do chip em modo Deep-sleep.

Obs.: As instruções específicas do ULP-FSM são documentadas no manual técnico ([docs.espressif.com][3]).

---

## 3. Como Compilar e Usar

### a) Ferramentas

Use o **ESP-IDF**, que já inclui o toolchain RISC-V e suporte ao ULP-RISC-V ([docs.espressif.com][1]).

### b) Workflow Básico

1. Crie arquivo `.S` com código Assembly.
2. Adicione ao componente com `ulp_embed_binary(...)` no CMakeLists ([docs.espressif.com][1]).
3. Compile e o código será embutido e executado no ULP-RISC-V do ESP32-S3.

### c) Público

Ideal para:

* Tarefas de *ultra baixo consumo* (sensoriamento, wake-up sem ativar CPU principal).
* Otimização crítica (uso de instruções SIMD que aceleram cálculos críticos, exemplo: multiplicação vetorial até 44× mais rápida que loops comuns) ([Reddit][5]).

---

## Resumo Rápido

| Núcleo     | ISA / Recursos                       | Uso típico                               |
| ---------- | ------------------------------------ | ---------------------------------------- |
| ULP-RISC-V | RISC-V RV32IMC + compressed instr.   | Sensoriamento, loops eficientes, C & ASM |
| ULP-FSM    | FSM com 4 registradores + stage\_cnt | Lógica de máquina ultraleve e sleep      |

---

## Referências

[1]: https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/api-reference/system/ulp-risc-v.html?utm_source=chatgpt.com "ULP RISC-V Coprocessor Programming - ESP32-S3"
[2]: https://cdn-learn.adafruit.com/assets/assets/000/110/710/original/esp32-s3_technical_reference_manual_en.pdf?1649790877=&utm_source=chatgpt.com "[PDF] ESP32S3 - Technical Reference Manual - Adafruit"
[3]: https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/api-reference/system/ulp_instruction_set.html?utm_source=chatgpt.com "ESP32-S3 ULP Coprocessor Instruction Set - ESP32-S3 - — ESP-IDF ..."
[4]: https://stackoverflow.com/questions/78886679/compiling-and-loading-on-esp32-s3-assembler-code?utm_source=chatgpt.com "Compiling and loading on esp32-s3 assembler code"
[5]: https://www.reddit.com/r/esp32/comments/1hm91t0/simd_instructions_on_the_s3_are_fast/?utm_source=chatgpt.com "SIMD instructions on the S3 are fast! : r/esp32 - Reddit"

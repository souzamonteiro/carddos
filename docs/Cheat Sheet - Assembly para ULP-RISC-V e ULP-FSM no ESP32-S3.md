# Cheat Sheet: Assembly para ULP-RISC-V e ULP-FSM no ESP32-S3

## 1. Visão Geral dos Coprocessadores ULP

| Coprocessador  | ISA / Arquitetura                                                                                                                  | Uso Ideal                                                                            |
| -------------- | ---------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------ |
| **ULP-RISC-V** | RV32IMC (RISC-V 32-bit, com multiplicação/divisão e instruções comprimidas) ([docs.espressif.com][1], [cdn-learn.adafruit.com][2]) | Execução de programas em C ou Assembly mais complexos, cálculos, I/O com periféricos |
| **ULP-FSM**    | FSM com 4 registradores de 16 bits + `stage_cnt` (contador de estágios) ([docs.espressif.com][3], [cdn-learn.adafruit.com][2])     | Monitoramento de sensores, loops simples em modo de ultra-baixo consumo              |

---

## 2. Acesso e Memória

* Ambos os ULPs trabalham com **RTC\_SLOW\_MEM** (\~8 KB) acessível em palavras de 32 bits ([cdn-learn.adafruit.com][2]).
* Clock: aproximadamente **17.5 MHz (RTC\_FAST\_CLK)** ([cdn-learn.adafruit.com][2], [esp32.com][4]).
* Permissões de acesso a registradores e I/O de baixo consumo (`RTC_CNTL`, `RTC_IO`, `SARADC`, `TSENS`) disponíveis nos 2 modos ([docs.espressif.com][5]).

---

## 3. Principais Instruções do ULP-FSM

* **ALU Operations**: operações aritméticas básicas (add, sub, etc.)
* **LD / ST / REG\_RD / REG\_WR**: load/store de memória e leitura/gravação direta em registradores de periféricos ([cdn-learn.adafruit.com][2], [docs.espressif.com][5]).
* **JUMP**: pulo condicional ou incondicional, com endereços em palavras de 32 bits ([cdn-learn.adafruit.com][2], [docs.espressif.com][3]).
* **WAIT / HALT**: controla execução e modos de espera/power-down ([cdn-learn.adafruit.com][2]).
* **WAKE**: acorda a CPU principal ou envia sinais de interrupção ([cdn-learn.adafruit.com][2]).
* **TSENS / ADC**: permite leitura de sensor de temperatura ou conversor ADC diretamente do ULP ([cdn-learn.adafruit.com][2]).

---

## 4. Instruções RISC-V (ULP-RISC-V)

Baseado no conjunto **RV32IMC** — ISA padrão com suporte a multiplicação, divisão e instruções comprimidas ([docs.espressif.com][1], [Production ESP32][6], [Wikipedia][7]).

* **Aritmética**: `add`, `addi`, `sub`, `mul`, `div`
* **Load / Store**: `lw`, `sw`, `lb`, `sb`
* **Branches / Jumps**: `beq`, `bne`, `blt`, `bge`, `jal`, `jalr`
* **Comprimidas (C-Extension)**: instruções encurtadas (ex.: `c.addi`) para economizar espaço ([docs.espressif.com][1]).

---

## 5. Compilação e Workflow (ESP-IDF)

### ULP-FSM

1. Escrever em **Assembly (.S)** na pasta `ulp/` do componente.
2. Compilar com **binutils-esp32ulp** via CMake do ESP-IDF ([docs.espressif.com][5]).

### ULP-RISC-V

1. Programar em **C ou Assembly**.
2. Compilar com toolchain RISC-V GCC (já incluído no ESP-IDF) ([docs.espressif.com][1]).

---

## 6. Dicas e Observações

* Use **ULP-RISC-V** se precisar de código mais elaborado ou usar o compilador padrão; ideal para C + Assembly.
* Use **ULP-FSM** para tarefas específicas, ultra-baixo consumo, sensores e lógica simples com economia máxima de energia.
* O relógio de trabalho típico (8 MHz ou 17.5 MHz) precisa ser considerado ao calcular delays ou temporizações precisas ([esp32.com][4]).

---

> **Conclusão**: Este cheat sheet resume o essencial dos ULPs do ESP32-S3 — características, instruções, compilação e casos de uso — para você começar rápido. Assim, fica mais fácil escolher entre ULP-FSM ou ULP-RISC-V e escrever código otimizado conforme a necessidade.

## Referências

[1]: https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/api-reference/system/ulp-risc-v.html?utm_source=chatgpt.com "ULP RISC-V Coprocessor Programming - ESP32-S3"
[2]: https://cdn-learn.adafruit.com/assets/assets/000/110/710/original/esp32-s3_technical_reference_manual_en.pdf?1649790877=&utm_source=chatgpt.com "[PDF] ESP32S3 - Technical Reference Manual - Adafruit"
[3]: https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/api-reference/system/ulp_instruction_set.html?utm_source=chatgpt.com "ESP32-S3 ULP Coprocessor Instruction Set - Espressif Systems"
[4]: https://esp32.com/viewtopic.php?t=20919&utm_source=chatgpt.com "ESP32-S2 ULP-RISC-V clock frequency? Microsecond delay"
[5]: https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/system/ulp-fsm.html?utm_source=chatgpt.com "ULP FSM Coprocessor Programming - ESP32 - Espressif Systems"
[6]: https://productionesp32.com/posts/ulp-under-the-hood/?utm_source=chatgpt.com "#29: ULP Series - Under the Hood | Production ESP32"
[7]: https://en.wikipedia.org/wiki/RISC-V_instruction_listings?utm_source=chatgpt.com "RISC-V instruction listings"

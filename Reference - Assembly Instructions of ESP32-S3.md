# Reference: Assembly Instructions of ESP32-S3

## 1. ULP-RISC-V Instructions (RV32IMC + Compressed)

The ESP32-S3’s ULP-RISC-V core supports the RV32IMC instruction set:

| Instruction | Description                               | Syntax / Notes          |
| ----------- | ----------------------------------------- | ----------------------- |
| `ADD`       | Add two registers                         | `ADD rd, rs1, rs2`      |
| `ADDI`      | Add immediate to register                 | `ADDI rd, rs1, imm`     |
| `SUB`       | Subtract registers                        | `SUB rd, rs1, rs2`      |
| `MUL`       | Multiply registers                        | `MUL rd, rs1, rs2`      |
| `DIV`       | Divide registers                          | `DIV rd, rs1, rs2`      |
| `REM`       | Remainder after division                  | `REM rd, rs1, rs2`      |
| `AND`       | Bitwise AND                               | `AND rd, rs1, rs2`      |
| `OR`        | Bitwise OR                                | `OR rd, rs1, rs2`       |
| `XOR`       | Bitwise XOR                               | `XOR rd, rs1, rs2`      |
| `SLL`       | Shift left logical                        | `SLL rd, rs1, rs2`      |
| `SRL`       | Shift right logical                       | `SRL rd, rs1, rs2`      |
| `SRA`       | Shift right arithmetic                    | `SRA rd, rs1, rs2`      |
| `SLT`       | Set less than (signed)                    | `SLT rd, rs1, rs2`      |
| `SLTU`      | Set less than (unsigned)                  | `SLTU rd, rs1, rs2`     |
| `LB`        | Load byte (sign-extended)                 | `LB rd, offset(rs1)`    |
| `LH`        | Load halfword (sign-extended)             | `LH rd, offset(rs1)`    |
| `LW`        | Load word                                 | `LW rd, offset(rs1)`    |
| `LBU`       | Load byte unsigned                        | `LBU rd, offset(rs1)`   |
| `LHU`       | Load halfword unsigned                    | `LHU rd, offset(rs1)`   |
| `SB`        | Store byte                                | `SB rs2, offset(rs1)`   |
| `SH`        | Store halfword                            | `SH rs2, offset(rs1)`   |
| `SW`        | Store word                                | `SW rs2, offset(rs1)`   |
| `BEQ`       | Branch if equal                           | `BEQ rs1, rs2, label`   |
| `BNE`       | Branch if not equal                       | `BNE rs1, rs2, label`   |
| `BLT`       | Branch if less than (signed)              | `BLT rs1, rs2, label`   |
| `BGE`       | Branch if greater or equal (signed)       | `BGE rs1, rs2, label`   |
| `BLTU`      | Branch if less than (unsigned)            | `BLTU rs1, rs2, label`  |
| `BGEU`      | Branch if greater or equal (unsigned)     | `BGEU rs1, rs2, label`  |
| `JAL`       | Jump and link (call)                      | `JAL rd, label`         |
| `JALR`      | Jump and link register                    | `JALR rd, rs1, imm`     |
| `LUI`       | Load upper immediate                      | `LUI rd, imm`           |
| `AUIPC`     | Add upper immediate to PC                 | `AUIPC rd, imm`         |
| `NOP`       | No operation                              | `NOP`                   |
| `C.ADDI`    | Compressed add immediate                  | `C.ADDI rd, imm`        |
| `C.LW`      | Compressed load word                      | `C.LW rd, offset(rs1)`  |
| `C.SW`      | Compressed store word                     | `C.SW rs2, offset(rs1)` |
| …           | *(and many more compressed instructions)* |                         |

**Notes:**

* Compressed instructions (`C.*`) reduce code size, often 16 bits long.
* RV32IMC means base RV32I + Multiply/Divide + Compressed extension.

---

## 2. ULP-FSM Instructions (ESP32-S3 Specific)

The Ultra Low Power Finite State Machine (ULP-FSM) has a smaller, specialized instruction set optimized for low power tasks.

| Instruction | Description                                   | Syntax / Notes             |
| ----------- | --------------------------------------------- | -------------------------- |
| `ALU`       | Arithmetic/Logic operation on registers R0-R3 | `ALU op, Rd, Rs`           |
| `LD`        | Load word from memory to register             | `LD Rd, addr`              |
| `ST`        | Store register to memory                      | `ST Rs, addr`              |
| `REG_RD`    | Read peripheral register                      | `REG_RD Rd, reg_addr`      |
| `REG_WR`    | Write to peripheral register                  | `REG_WR Rs, reg_addr`      |
| `JUMP`      | Jump to address (conditional/unconditional)   | `JUMP addr` or conditional |
| `WAIT`      | Wait cycles or event                          | `WAIT n`                   |
| `HALT`      | Stop execution until wake-up                  | `HALT`                     |
| `WAKE`      | Wake main CPU                                 | `WAKE`                     |
| `INC`       | Increment register                            | `INC Rd`                   |
| `DEC`       | Decrement register                            | `DEC Rd`                   |
| `CMP`       | Compare registers                             | `CMP Rs1, Rs2`             |
| `NOP`       | No operation                                  | `NOP`                      |

---

## 3. Helpful Tips and Resources

* Official ULP instruction set detailed in [ESP-IDF documentation](https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/api-reference/system/ulp_instruction_set.html).
* ULP-RISC-V ISA reference: [RISC-V specs](https://riscv.org/specifications/).
* To write assembly for ESP32-S3 ULP:

  * Use `ulp-riscv-elf` toolchain from ESP-IDF.
  * Refer to example projects in [Espressif’s GitHub](https://github.com/espressif/esp-idf/tree/master/examples/system/ulp_riscv).

---


addi sp, x0, 0x100   # sp = 0x100
addi x1, x0, 0x1234  # x1 = 0x1234
sw x1, 8(sp)         # Mem[0x108] = 0x1234
lw x2, 8(sp)         # x2 = 0x1234
addi a7, x0, 10
ecall
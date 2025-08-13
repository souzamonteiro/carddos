addi sp, x0, 0x100
lui x1, 0x12345      # x1 = 0x12345000
addi x2, x0, 0x678
add x3, x1, x2       # x3 = 0x12345678
sw x3, 0(sp)
lw x4, 0(sp)
beq x3, x4, label
addi x5, x0, 1       # Não executado
label:
addi a7, x0, 10
ecall
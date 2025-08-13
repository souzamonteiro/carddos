addi x1, x0, 5       # x1 = 5
addi x2, x0, 3       # x2 = 3
add x3, x1, x2       # x3 = 8 (5+3)
sub x4, x1, x2       # x4 = 2 (5-3)
xor x5, x1, x2       # x5 = 6 (5 XOR 3)
addi a7, x0, 10      # syscall exit
ecall
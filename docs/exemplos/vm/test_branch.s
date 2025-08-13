addi x1, x0, 5       # x1 = 5
addi x2, x0, 5       # x2 = 5
beq x1, x2, label    # Deve pular para label
addi x3, x0, 1       # Não executado
label:
addi x4, x0, 2       # x4 = 2
addi a7, x0, 10      # syscall exit
ecall

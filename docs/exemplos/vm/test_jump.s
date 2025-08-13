addi x1, x0, 1
jal x10, target      # x10 = PC+4, jump para target
addi x1, x0, 2       # Não executado
target:
addi x2, x0, 3
addi a7, x0, 10
ecall
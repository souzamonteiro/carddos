start:
    addi x1, x0, 5
    addi x2, x0, 5
    beq x1, x2, start  # Deve criar um loop infinito
    addi x3, x0, 1     # Nunca executado
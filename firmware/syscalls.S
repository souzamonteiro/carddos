/* Handler de syscall (invocado via 'syscall') */
.section .text
.global syscall_entry
syscall_entry:
    /* Salva registradores */
    s32i    a0, a1, 0
    s32i    a2, a1, 8
    /* Chama o handler em C (a2 = syscall_num, a3 = arg1, a4 = arg2) */
    call0   syscall_handler
    /* Restaura registradores e retorna */
    l32i    a0, a1, 0
    l32i    a2, a1, 8
    ret

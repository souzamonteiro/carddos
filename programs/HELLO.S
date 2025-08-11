/* HELLO.COM: Imprime uma mensagem e sai */
.section .text
.global _start
_start:
    /* Syscall SYS_PRINT */
    movi    a2, 0x09       /* Serviço "print" */
    movi    a3, msg        /* String */
    syscall

    /* Syscall SYS_EXIT */
    movi    a2, 0x4C       /* Serviço "exit" */
    movi    a3, 0x00       /* Código de retorno */
    syscall

msg: .string "Olá, CardDOS!\n"

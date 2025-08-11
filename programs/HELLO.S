/* HELLO.COM: Prints a message and exits. */
.section .text
.global _start
_start:
    /* Syscall SYS_PRINT */
    movi    a2, 0x09       /* Service "print". */
    movi    a3, msg        /* String. */
    syscall

    /* Syscall SYS_EXIT */
    movi    a2, 0x4C       /* Service "exit". */
    movi    a3, 0x00       /* Return code. */
    syscall

msg: .string "Hello, CardDOS!\n"

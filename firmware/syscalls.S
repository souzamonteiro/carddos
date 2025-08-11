/* Syscall handler (invoked via 'syscall'). */
.section .text
.global syscall_entry
syscall_entry:
    /* Save registers. */
    s32i    a0, a1, 0
    s32i    a2, a1, 8
    /* Calls the C handler (a2 = syscall_num, a3 = arg1, a4 = arg2). */
    call0   syscall_handler
    /* Restores registers and returns. */
    l32i    a0, a1, 0
    l32i    a2, a1, 8
    ret

/* Bootloader: Loads the kernel and shell. */
.section .boot, "ax"
.global _start
_start:
    /* 1. Configure basic hardware. */
    movi    a1, 0x3FFB0000  /* Stack pointer. */
    movi    a2, 0x9000      /* Kernel offset on flash. */
    movi    a3, 0x3FFC0000  /* Destination in RAM. */
    call0   spi_flash_read  /* Load kernel. */

    /* 2. Jump to kernel. */
    movi    a0, 0x3FFC0000
    jx      a0

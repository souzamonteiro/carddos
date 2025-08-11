/* Bootloader: Carrega o kernel e o shell */
.section .boot, "ax"
.global _start
_start:
    /* 1. Configura hardware básico */
    movi    a1, 0x3FFB0000  /* Stack pointer */
    movi    a2, 0x9000      /* Offset do kernel na flash */
    movi    a3, 0x3FFC0000  /* Destino na RAM */
    call0   spi_flash_read  /* Carrega kernel */

    /* 2. Salta para o kernel */
    movi    a0, 0x3FFC0000
    jx      a0

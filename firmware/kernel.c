#include <stdint.h>

/* Syscalls do CardDOS */
#define SYS_PRINT 0x09
#define SYS_EXIT  0x4C

void syscall_handler(uint32_t syscall_num, uint32_t arg1, uint32_t arg2) {
    switch (syscall_num) {
        case SYS_PRINT:
            display_print((char*)arg1);  // Implemente display_print()
            break;
        case SYS_EXIT:
            current_task_exit(arg1);     // Implemente task_exit()
            break;
    }
}

void load_program(const char *filename, uint32_t addr) {
    FILE *fp = fopen(filename, "rb");
    if (fp) {
        fread((void*)addr, 1, file_size(fp), fp);
        fclose(fp);
        ((void(*)(void))addr)();  // Executa o programa
    }
}

void kernel_main() {
    /* Inicializa hardware */
    display_init();
    keyboard_init();

    /* Carrega e executa o shell (CARDOM.COM) */
    load_program("0:/CARDOM.COM", 0x1000);  // Implemente load_program()
}
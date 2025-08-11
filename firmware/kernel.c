#include <stdint.h>

/* CardDOS syscalls. */
#define SYS_PRINT 0x09
#define SYS_EXIT  0x4C

void syscall_handler(uint32_t syscall_num, uint32_t arg1, uint32_t arg2) {
    switch (syscall_num) {
        case SYS_PRINT:
            display_print((char*)arg1);  // Implement display_print()
            break;
        case SYS_EXIT:
            current_task_exit(arg1);     // Implement task_exit()
            break;
    }
}

void load_program(const char *filename, uint32_t addr) {
    FILE *fp = fopen(filename, "rb");
    if (fp) {
        fread((void*)addr, 1, file_size(fp), fp);
        fclose(fp);
        ((void(*)(void))addr)();  // Execute the program.
    }
}

void kernel_main() {
    /* Initialize hardware. */
    display_init();
    keyboard_init();

    /* Load and run the shell (CARDOM.COM). */
    load_program("0:/CARDOM.COM", 0x1000);
}
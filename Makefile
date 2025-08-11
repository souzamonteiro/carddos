CC = xtensa-esp32s3-elf-gcc
CFLAGS = -nostdlib -Wl,--oformat=binary

all: kernel.bin HELLO.COM

kernel.bin: firmware/boot.S firmware/kernel.c firmware/syscalls.S
    $(CC) -T linker.ld $^ -o $@

HELLO.COM: programs/HELLO.S
    $(CC) $(CFLAGS) $^ -o $@

clean:
    rm -f kernel.bin HELLO.COM

CC = xtensa-esp32s3-elf-gcc
CFLAGS = -nostdlib -Wl,--oformat=binary

all: kernel.bin HELLO.COM

kernel.bin: firmware/boot.S firmware/kernel.c firmware/syscalls.S
    $(CC) -T linker.ld $^ -o $@

background.bin: images/CardDOS-Background.png
    ffmpeg -i images/CardDOS-Background.png -vf scale=135:240 -pix_fmt rgb565 -f rawvideo -y background.bin
    
HELLO.COM: programs/HELLO.S
    $(CC) $(CFLAGS) $^ -o $@

clean:
    rm -f kernel.bin HELLO.COM

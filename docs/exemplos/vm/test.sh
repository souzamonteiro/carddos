#!/bin/sh

rm -f *.o *.bin

for f in `ls *.s`
do
    echo "Assembling file $f..."

    riscv64-unknown-elf-as $f -o $f.o
    riscv64-unknown-elf-objcopy -O binary $f.o $f.o.bin
    
    ./riscv_assembler $f $f.bin

    if [ -f "$f" ] && [ "$f" != "test_loop.s" ] && [ "$f" != "test_jump.s" ]; then
        ./riscv_vm $f.o.bin > $f.o.bin.txt
        ./riscv_vm $f.bin > $f.bin.txt
    fi
done

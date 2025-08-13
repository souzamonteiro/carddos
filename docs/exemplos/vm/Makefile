all: riscv_vm riscv_assembler

riscv_vm: riscv_vm.c
	gcc riscv_vm.c -o riscv_vm

riscv_assembler: riscv_assembler.c
	gcc riscv_assembler.c -o riscv_assembler

clean:
	rm -f riscv_vm riscv_assembler

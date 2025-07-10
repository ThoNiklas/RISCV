
SOURCE = ./src
CONFIG = $(SOURCE)/config
RTL = $(SOURCE)/rtl
TB = $(SOURCE)/tb
ASSEMBLER = ./tools/main.py
CODE = ./code/test.asm
ROM = $(SOURCE)/mem/bin_rom.mem



run: write_rom riscv_tb
	./obj_dir/Vriscv_tb

riscv_tb: 
	verilator --binary -j 0 -Wall --trace -I$(CONFIG) $(RTL)/*.sv $(TB)/*.sv $(CONFIG)/*.svh --top-module riscv_tb

write_rom:
	python $(ASSEMBLER) $(CODE) $(ROM)

wave: run
	gtkwave riscv_tb.vcd

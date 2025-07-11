
SOURCE = ./src
RTL = $(SOURCE)/rtl
TB = $(SOURCE)/tb
ASSEMBLER = ./tools/main.py
CODE = ./code/test.asm
ROM = $(SOURCE)/mem/bin_rom.mem
OBJDIR = ./obj_dir
VCD_ENV = riscv_env.vcd
VCD_SC = riscv_sc


run_env: write_rom riscv
	$(OBJDIR)/Vriscv_env

run_sc: write_rom riscv_sc
	$(OBJDIR)/Vriscv riscv_sc

riscv_sc: 
	verilator --sc --exe -j 0 -Wall -DTB $(RTL)/*.sv $(TB)/sc_main.cpp --top-module riscv -build

riscv: 
	verilator --binary -j 0 -Wall --trace $(RTL)/*.sv $(TB)/*.sv --top-module riscv_env

write_rom:
	python $(ASSEMBLER) $(CODE) $(ROM)

wave_env: run_env
	gtkwave $(VCD_ENV)

wave_sc: run_sc
	gtkwave $(VCD_SC).vcd

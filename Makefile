
SOURCE = ./src
CONFIG = $(SOURCE)/config
RTL = $(SOURCE)/rtl
TB = $(SOURCE)/tb

riscv_tb:
	verilator --binary -j 0 -Wall --trace -I$(CONFIG) $(RTL)/*.sv $(TB)/*.sv $(CONFIG)/*.svh --top-module riscv_tb

/* verilator lint_off UNUSEDSIGNAL */

module InstructionMemory #(parameter REG_BITS=32) 
(
    input logic  [REG_BITS-1:0] A,
    output logic  [REG_BITS-1:0] RD
);

    reg [REG_BITS-1:0] mem [0 : 2 ** 15 - 1];
    initial begin
        $display("Read Rom");
        $readmemh("./mem/hex_rom.mem", mem); // load hex file
        //$readmemb("../mem/bin_rom.mem", mem); // load bin file

    end

    assign RD = mem[A];

endmodule


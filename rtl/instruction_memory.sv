/* verilator lint_off UNUSEDSIGNAL */

module instruction_memory #(parameter RegBits=32) 
(
    input logic  [RegBits-1:0] a_i,
    output logic  [RegBits-1:0] rd_o
);

    reg [RegBits-1:0] mem [0 : 2 ** 15 - 1];
    initial begin
        $display("Read ROM");
        $readmemh("./mem/hex_rom.mem", mem); // load hex file
        //$readmemb("../mem/bin_rom.mem", mem); // load bin file

    end

    assign rd_o = mem[a_i];

endmodule


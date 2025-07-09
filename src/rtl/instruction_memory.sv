/* verilator lint_off UNUSEDSIGNAL */

module instruction_memory #(parameter RegBits=32) 
(
    input logic  [RegBits-1:0] a_i,
    output logic  [RegBits-1:0] rd_o
);

    //reg [RegBits-1:0] mem [0 : 2 ** 15 - 1];
    reg [7 : 0] mem [2 ** 15 - 1:0];
    initial begin
        $display("Read ROM");
        //$readmemh("./mem/hex_rom.mem", mem); // load hex file
        $readmemb("./src/mem/bin_rom.mem", mem); // load bin file

    end

    assign rd_o = {mem[a_i], mem[a_i+1], mem[a_i+2], mem[a_i+3]};

endmodule


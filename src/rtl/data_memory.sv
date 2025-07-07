/* verilator lint_off UNUSEDSIGNAL */

module data_memory #(parameter RegBits=32) 
(
    input logic  [RegBits-1:0] a_i,
    input logic [RegBits-1:0] wd_i,
    input logic clk_i, we_i,
    output logic  [RegBits-1:0] rd_o
);

    //reg [RegBits-1:0] mem [2 ** 10-1:0];
    reg [7:0] mem [2**10-1:0]; // make it byte-adressable

    initial begin
        $display("Read RAM");
        $readmemh("./mem/hex_ram.mem", mem); // load hex file
        //$readmemb("../mem/bin_ram.mem", mem); // load bin file

    end

    always_comb begin
        rd_o = {mem[a_i], mem[a_i+1], mem[a_i+2], mem[a_i+3]} ;
    end

    always_ff @(posedge clk_i) begin
       if (we_i) begin
            mem[a_i+3] <= wd_i[31:24];
            mem[a_i+2] <= wd_i[23:16];
            mem[a_i+1] <= wd_i[15:8];
            mem[a_i] <= wd_i[7:0];
       end
    end

endmodule


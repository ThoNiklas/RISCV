/* verilator lint_off UNUSEDSIGNAL */

module data_memory #(parameter RegBits=32) 
(
    input logic  [RegBits-1:0] a_i,
    input logic [RegBits-1:0] wd_i,
    input logic clk_i, we_i,
    output logic  [RegBits-1:0] rd_o
);

    logic [RegBits-1:0] mem [2 ** 10-1:0];

    initial begin
        $display("Read RAM");
        $readmemh("./mem/hex_ram.mem", mem); // load hex file
        //$readmemb("../mem/bin_ram.mem", mem); // load bin file

    end

    always_comb begin
        rd_o = mem[a_i];
    end

    always_ff @(posedge clk_i) begin
       if (we_i) begin
            mem[a_i] <= wd_i;
       end
    end

endmodule


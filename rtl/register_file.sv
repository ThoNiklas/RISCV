module register_file #( parameter RegBits = 32, parameter AddrBits = 5)
(
    input logic clk_i, rst_i, we3_i,
    input logic[AddrBits-1:0] a1_i, a2_i, a3_i,
    input logic[RegBits-1:0] wd3_i,
    output logic [RegBits-1:0] rd1_o, rd2_o
);
    logic [RegBits - 1:0] rf [2 ** AddrBits - 1 : 0];

    always_comb begin
        rf[0] = 'b0;
        rd1_o = rf[a1_i];
        rd2_o = rf[a2_i];
    end

    always_ff @(posedge clk_i or negedge rst_i) begin
        int c;
        if (!rst_i) begin
            for (c=0; c<2 ** AddrBits - 1; c=c+1) rf[c] <= 'b0;
        end 
        else if (we3_i) begin
            rf[a3_i] <= wd3_i; 
        end
    end

endmodule


module RegisterFile #( parameter REG_BITS = 32, parameter ADDR_BITS = 5)
(
    input logic clk, rst, we3,
    input logic[ADDR_BITS-1:0] a1, a2, a3,
    input logic[REG_BITS-1:0] wd3,
    output logic [REG_BITS-1:0] rd1, rd2
);
    logic [REG_BITS - 1:0] rf [2 ** ADDR_BITS - 1 : 0];

    always_comb begin
        rf[0] = 'b0;
        rd1 = rf[a1];
        rd2 = rf[a2];
    end

    always_ff @(posedge clk or negedge rst) begin
        int c;
        if (!rst) begin
            for (c=0; c<2 ** ADDR_BITS - 1; c=c+1) rf[c] <= 'b0;
        end 
        else if (we3) begin
            rf[a3] <= wd3; 
        end
    end

endmodule


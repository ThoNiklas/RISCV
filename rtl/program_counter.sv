module program_counter #( parameter RegBits=32)
(
    input logic  clk_i, rst_i,
    input logic [RegBits-1:0] pc_next_i,
    output logic  [RegBits-1:0] pc_o
);
    always_ff @(posedge clk_i or negedge rst_i) begin
        if (!rst_i) pc_o <= 'b0;
        else pc_o <= pc_next_i;
    end
endmodule


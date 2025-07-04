module program_counter #( parameter RegBits=32)
(
    input logic  clk, rst,
    input logic [RegBits-1:0] pc_next,
    output logic  [RegBits-1:0] pc
);
    always_ff @(posedge clk or negedge rst) begin
        if (!rst) pc <= 'b0;
        else pc <= pc_next;
    end
endmodule


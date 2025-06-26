module ProgramCounter #( parameter REG_BITS=32)
(
    input logic  clk, rst,
    input logic [REG_BITS-1:0] pcNext,
    output logic  [REG_BITS-1:0] pc
);
    always_ff @(posedge clk or negedge rst) begin
        if (!rst) pc <= 'b0;
        else pc <= pcNext;
    end
endmodule


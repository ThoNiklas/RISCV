module ALU #(parameter REG_BITS=32)
(
    input logic [REG_BITS-1:0] A, B,
    input logic [3:0] ctrl,
    output logic [2:0] ONZ,
    output logic [REG_BITS-1:0] C 
);

endmodule


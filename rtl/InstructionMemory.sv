module InstructionMemory #(parameter REG_BITS=32) 
(
    input logic  [REG_BITS-1:0] a,
    output logic  [REG_BITS-1:0] rd
);

    reg [REG_BITS-1:0] mem [0 : 2 ** REG_BITS - 1] = '{default:0};
    assign mem[1] = 32'b1;

    assign rd = mem[a];
endmodule


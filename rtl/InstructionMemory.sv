module InstructionMemory #(parameter REG_BITS=32) 
(
    input logic  [REG_BITS-1:0] a,
    output logic  [REG_BITS-1:0] rd
);

    logic [REG_BITS-1:0] mem [REG_BITS-1:0];

    always_comb begin
        rd = mem[a];
    end
endmodule


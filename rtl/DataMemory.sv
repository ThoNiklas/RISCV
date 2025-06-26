module DataMemory #(parameter REG_BITS=32) 
(
    input logic  [REG_BITS-1:0] a,
    input logic [REG_BITS-1:0] wd,
    input logic clk, we,
    output logic  [REG_BITS-1:0] rd
);

    logic [REG_BITS-1:0] mem [REG_BITS-1:0];

    always_comb begin
        rd = mem[a];
    end

    always_ff @(posedge clk) begin
       if (we) begin
            mem[a] = wd;
       end
    end

endmodule


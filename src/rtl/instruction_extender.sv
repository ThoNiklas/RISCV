module instruction_extender #(parameter RegBits = 32) (
    input logic [RegBits-1 : 0] in,
    output logic [RegBits-1 : 0] out,
    output logic pc_plus_2
);

    logic [1:0] quadrant = in[1:0];

    always_comb begin : 
        case(quadrant)
            2'b00: begin
                pc_plus_2 = 1'b1;

            end
            2'b01: begin
                pc_plus_2 = 1'b1;

            end
            2'b10: begin
                pc_plus_2 = 1'b1;

            end
            2'b11: begin
                out = in;
                pc_plus_2 = 1'b0;
            end
    end

endmodule


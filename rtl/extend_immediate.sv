module extend_immediate #(parameter RegBits=32)
(
    input logic [24:0] in_i,
    input logic [2:0] immediate_source_i,
    output logic [RegBits-1:0] out_o
);
    always_comb begin
        case(immediate_source_i)
            3'b000:
                out_o = {{20{in_i[24]}}, in_i[24:13]};
            3'b001:
                out_o = {{20{in_i[24]}}, in_i[24:18], in_i[4:0]};
            3'b010:
                out_o = {{20{in_i[24]}}, in_i[0], in_i[23:18], in_i[4:1], 1'b0};
            3'b011:
                out_o = {in_i[24:5], {12{1'b0}}};
            3'b100:
                out_o = {{12{in_i[24]}}, in_i[12:5], in_i[13], in_i[23:14], 1'b0};
            default:
                out_o = 'b0;
        endcase
    end


endmodule


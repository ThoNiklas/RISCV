module extend_result #(parameter RegBits=32)
(
    input logic [RegBits-1:0] in_i,
    input logic [2:0] result_extend_control_i,
    output logic [RegBits-1:0] out_o
);
    always_comb begin 
       case(result_extend_control_i)
           3'b000:
               out_o = in_i;
           3'b001:
               out_o = {{24{in_i[7]}}, in_i[7:0]};
           3'b010:
               out_o = {{16{in_i[7]}}, in_i[15:0]};
           3'b101:
               out_o = {{24{1'b0}}, in_i[7:0]};
           3'b110:
               out_o = {{16{1'b0}}, in_i[15:0]};
           default:
               out_o = 'b0;
       endcase
    end

endmodule


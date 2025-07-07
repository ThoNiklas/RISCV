module alu #(parameter RegBits=32)
(
    input logic [RegBits-1:0] a_i, b_i,
    input logic [3:0] ctrl_i,
    output logic [3:0] onzc_o,
    output logic [RegBits-1:0] c_o 
);

   logic [RegBits:0] tmp_result;
   logic [RegBits:0] tmp;

   always_comb begin
       onzc_o = 4'b0000;
       tmp_result = 0;
       tmp = 0;
       case(ctrl_i)
           4'b0000: begin //add
                tmp_result = a_i + b_i;
                c_o = tmp_result[RegBits-1:0];
                onzc_o[0] = tmp_result[RegBits];
                if (c_o == 0) onzc_o[1] = 1;
                if (c_o[RegBits-1] == 1) onzc_o[2] = 1; 
                if ((a_i[RegBits-1] == b_i[RegBits-1]) && (a_i[RegBits-1] != c_o[RegBits-1])) onzc_o[3] = 1;
           end
           4'b0001:begin  //sub
                tmp_result = a_i - b_i;
                c_o = tmp_result[RegBits-1:0];
                onzc_o[0] = tmp_result[RegBits];
                if (c_o[RegBits-1] == 1) onzc_o[2] = 1; 
                if ((a_i[RegBits-1] == b_i[RegBits-1]) && (a_i[RegBits-1] != c_o[RegBits-1])) onzc_o[3] = 1;
           end
           4'b0010: //and 
                c_o = a_i & b_i;
           4'b0011: //or
                c_o = a_i | b_i;
           4'b0100: //xor
                c_o = a_i ^ b_i;
           4'b0101: begin//slt
                if ($signed(a_i) < $signed(b_i)) c_o = 1;
                else c_o = 0;
           end
           4'b0110: begin  //sll
                tmp = {1'b0, a_i} << b_i[4:0];
                c_o = tmp[RegBits-1:0];
                onzc_o[0] = tmp[RegBits];
           end
           4'b0111: begin//sltu
               if ($unsigned(a_i) < $unsigned(b_i)) c_o = 1;
               else c_o = 0;
           end
           4'b1000: begin//srl
                tmp = {a_i, 1'b0} >> b_i[4:0];
                c_o = tmp[RegBits:1];
                onzc_o[0] = tmp[0];
           end
           4'b1001: begin //sra
                tmp = $signed({a_i, 1'b0}) >>> b_i[4:0];
                c_o = tmp[RegBits:1];
                onzc_o[0] = tmp[0];
           end
           4'b1010: begin //subu
               tmp_result = $unsigned(a_i) - $unsigned(b_i);
               onzc_o[3] = tmp_result[RegBits];
               c_o = tmp_result[RegBits-1:0];
           end
           default:
                c_o = 'b0;
       endcase
       if (c_o == 0) onzc_o[1] = 1;
   end

endmodule


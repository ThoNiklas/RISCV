module alu_decoder (
    input logic [1:0] alu_op_i, op_funct7_i,
    input logic [2:0] funct3_i,
    output logic [3:0] alu_control_o
);

    always_comb begin
        case(alu_op_i)
            2'b00: alu_control_o = 4'b0000; // I/S/U/Type
            2'b01: alu_control_o = 4'b0001; // B-Type
            2'b10: begin
                case (funct3_i)
                    3'b000: begin
                        if (op_funct7_i == 2'b11) alu_control_o = 4'b0001; // sub
                        else alu_control_o = 4'b0000; // add
                    end
                    3'b001: alu_control_o = 4'b0110; // sll
                    3'b010: alu_control_o = 4'b0101; // slt
                    3'b011: alu_control_o = 4'b0111; // sltu
                    3'b100: alu_control_o = 4'b0100; // xor
                    3'b101: begin
                        if (op_funct7_i[0] == 1'b1) alu_control_o = 4'b1001; // sra
                        else alu_control_o = 4'b1000; // srl
                    end
                    3'b110: alu_control_o = 4'b0011; // or
                    3'b111: alu_control_o = 4'b0010; // and
                endcase
            end
            2'b11: alu_control_o = 4'b1010; // subu
            default: alu_control_o = 4'b0000;
        endcase
    end

endmodule


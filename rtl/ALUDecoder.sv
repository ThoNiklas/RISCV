module ALUDecoder (
    input logic [1:0] ALUOp, OPFunct7,
    input logic [2:0] Funct3,
    output logic [3:0] ALUControl
);

    always_comb begin
        case(ALUOp)
            2'b00: ALUControl = 4'b0000; // I/S/U/Type
            2'b01: ALUControl = 4'b0001; // B-Type
            2'b10: begin
                case (Funct3)
                    3'b000: begin
                        if (OPFunct7 == 2'b11) ALUControl = 4'b0001; // sub
                        else ALUControl = 4'b0000; // add
                    end
                    3'b001: ALUControl = 4'b0110; // sll
                    3'b010: ALUControl = 4'b0101; // slt
                    3'b011: ALUControl = 4'b0111; // sltu
                    3'b100: ALUControl = 4'b0100; // xor
                    3'b101: begin
                        if (OPFunct7[0] == 1'b1) ALUControl = 4'b1001; // sra
                        else ALUControl = 4'b1000; // srl
                    end
                    3'b110: ALUControl = 4'b0011; // or
                    3'b111: ALUControl = 4'b0010; // and
                endcase
            end
            2'b11: ALUControl = 4'b1010; // subu
            default: ALUControl = 4'b0000;
        endcase
    end

endmodule


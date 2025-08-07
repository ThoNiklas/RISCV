module instruction_extender #(parameter RegBits = 32) (
    input logic [RegBits-1 : 0] in_i,
    output logic [RegBits-1 : 0] out_o,
    output logic pc_plus_2_o
);

    logic [1:0] quadrant;
    logic [$clog2(RegBits):0] rd, rs1, rs2;
    logic [RegBits-1:0] imm;
    logic [2:0] funct3;

    always_comb begin  
        quadrant = in_i[1:0];
        imm = 'b0;
        rd = 'b0;
        rs1 = 'b0;
        rs2 = 'b0;
        funct3 = in_i[15:13];

        case(quadrant)
            2'b00: begin
                pc_plus_2_o = 1'b1;

                case(funct3)
                    3'b000: begin // C.ADDI4SPN
                        rd = in[4:2] + 4'b1000;
                        imm[5:4] = in_i[12:11];
                        imm[9:6] = in_i[10:7];
                        imm[2] = in_i[6];
                        imm[3] = in_i[5];
                        out_o = imm[13:2] << 20 | 5'b00010 << 15 | 3'b000 << 12 | rd << 7 | 7'b0010011;
                    end
                    3'b010: begin //C.LW
                        rd = in[4:2] + 4'b1000;
                        rs1 = in_i[9:7] + 4'b1000;
                        imm[5:3] = in_i[12:10];
                        imm[2] = in_i[6];
                        imm[6] = in_i[5];
                        out_o = imm[11:0] << 20 | rs1 << 15 | 3'b010 << 12 | rd << 7 | 7'b0000011;
                    end
                    3'b110: begin // C.SW
                        rs1 = in_i[9:7] + 4'b1000;
                        rs2 = in_i[4:2] + 4'b1000;
                        imm[5:3] = in_i[12:10];
                        imm[2] = in_i[6];
                        imm[6] = in_i[5];
                        out_o = imm[11:5] << 25 | rs2 << 20 | rs1 << 15 | 3'b010 << 12 | imm[4:0] << 7 | 7'b0100011;
                    end
                    default:
                        rd = 'b0;
                endcase
            end
            2'b01: begin
                pc_plus_2_o = 1'b1;

                case(funct3)
                    3'b000: begin // C.NOP/ADDI
                        if (in_i[11:7] == 5'b00000)  begin //C.NOP
                            rd = 5'b00000;
                            out_o = 7'b0 << 25 | 5'b0 << 20 | 5'b0 << 15 | 3'b000 << 12 | 5'b0 << 7 | 7'b0110011;
                        end else begin // C.ADDI
                            rd = in_i[11:7];
                            imm[4:0] = in_i[6:2];
                            imm[RegBits-1:5] = {(RegBits-5){in_i[12]}};
                            out_o = imm[11:0] << 20 | rd << 15 | 3'b000 << 12 | rd << 7 | 7'b0010011;
                        end
                    end
                    3'b001: begin // C.JAL
                        imm[11] = in_i[12];
                        imm[4] = in_i[11];
                        imm[9:8] = in_i[10:9];
                        imm[10] = in_i[8];
                        imm[6] = in_i[7];
                        imm[7] = in_i[6];
                        imm[3:1] = in_i[5:3];
                        imm[5] = in_i[2];
                        out_o = imm[20] << 32 | imm[10:1] << 21 | imm[11] << 20 | imm[19:12] << 12 | 5'b00001 << 7 | 7'b1101111; 
                    end
                    3'b010:begin // C.LI
                       rd = in_i[11:7];
                       imm[4:0] = in_i[6:2];
                       imm[RegBits-1:5] = {(RegBits-5){in_i[12]}};
                       out_o = imm[11:0] << 20 | rd << 15 | 3'b000 << 12 | rd << 7 | 7'b0010011;
                    end
                    3'b011: begin // C.ADDI16SP/LUI
                        if (in_i[11:7] == 5'b00010) begin /// C.ADDI16SP
                            imm[4] = in_i[6];
                            imm[6] = in_i[5];
                            imm[8:7] = in_i[4:3];
                            imm[5] = in_i[2];
                            imm[RegBits-1:9] = {(RegBits-9){in_i[12]}};
                            out_o = imm[15:4] << 20 | 5'b00010 << 15 | 3'b000 << 12 | 5'b00010 << 7 | 7'b0010011;
                        end else begin // C.LUI
                            rd = in_i[11:7];
                            imm[16:12] = in_i[6:2];
                            imm[RegBits-1:17] = {(RegBits-17){in_i[12]}};
                            out_o = imm[31:12] << 12 | rd << 7 | 7'b0110111;
                        end
                    end
                    3'b100: begin // C.SRLI/SRAI/ANDI/SUB/XOR/OR/AND
                        case(in_i[11:10])
                            2'b00: begin // C.SRLI
                                rd = in_i[9:7] + 4'b1000;
                                imm[5] = in_i[12];
                                imm[4:0] = in_i[6:2];
                                out_o = imm[11:0] << 20 | rd << 15 | 3'b101 << 12 | rd << 7 | 7'b0010011;
                            end
                            2'b01: begin // C.SRAI
                                rd = in_i[9:7] + 4'b1000;
                                imm[5] = in_i[12];
                                imm[4:0] = in_i[6:2];
                                out_o = imm[11:0] << 20 | 1'b1 << 31 | rd << 15 | 3'b101 << 12 | rd << 7 | 7'b0010011;
                            end
                            2'b10: begin // C.ANDI
                                rd = in_i[9:7] + 4'b1000;
                                imm[4:0] = in_i[6:2];
                                imm[RegBits-1:5] = {(RegBits-5){in_i[12]}};
                                out_o = imm[11:0] << 20 | rd << 15 | 3'b111 << 12 | rd << 7 | 7'b0010011;
                            end
                            2'b11: begin
                                case(in_i[6:5])
                                    2'b00: begin // C.SUB
                                        rd = in_i[9:7] + 4'b1000;
                                        rs2 = in_i[4:2] + 4'b1000;
                                        out_o = 7'b0100000 << 25 | rs2 << 20 | rd << 15 | 3'b000 << 12 | rd << 7 | 7'b0110011;
                                    end
                                    2'b01: begin // C.XOR
                                        rd = in_i[9:7] + 4'b1000;
                                        rs2 = in_i[4:2] + 4'b1000;
                                        out_o = 7'b0 << 25 | rs2 << 20 | rd << 15 | 3'b100 << 12 | rd << 7 | 7'b0110011;
                                    end
                                    2'b10: begin // C.OR
                                        rd = in_i[9:7] + 4'b1000;
                                        rs2 = in_i[4:2] + 4'b1000;
                                        out_o = 7'b0 << 25 | rs2 << 20 | rd << 15 | 3'b110 << 12 | rd << 7 | 7'b0110011;
                                    end
                                    2'b11: begin // C.AND
                                        rd = in_i[9:7] + 4'b1000;
                                        rs2 = in_i[4:2] + 4'b1000;
                                        out_o = 7'b0 << 25 | rs2 << 20 | rd << 15 | 3'b111 << 12 | rd << 7 | 7'b0110011;
                                    end
                                endcase
                            end
                        endcase
                    end
                    3'b101: begin // C.J
                        imm[4] = in_i[11];
                        imm[9:8] = in_i[10:9];
                        imm[10] = in_i[8];
                        imm[6] = in_i[7];
                        imm[7] = in_i[6];
                        imm[3:1] = in_i[5:3];
                        imm[5] = in_i[2];
                        imm[RegBits-1:11] = {(RegBits-11){in_i[12]}};
                        out_o = imm[20] << 32 | imm[10:1] << 21 | imm[11] << 20 | imm[19:12] << 12 | 5'b00000 << 7 | 7'b1101111; 
                    end
                    3'b110: begin // C.BEQZ
                        rs1 = in_i[9:7] + 4'b1000;
                        imm[4:3] = in_i[11:10];
                        imm[7:6] = in_i[6:5];
                        imm[2:1] = in_i[4:3];
                        imm[5] = in_i[2];
                        imm[RegBits-1:8] = {(RegBits-8){in_i[12]}};
                        out_o = imm[12] << 32 | imm[10:5] << 25 | 5'b0 << 20 | rs1 << 15 || 3'b000 << 12 | imm[4:1] << 8 | imm[11] << 7 | 7'b1100011;
                    end  
                    3'b111: begin // C.BNEZ
                        rs1 = in_i[9:7] + 4'b1000;
                        imm[4:3] = in_i[11:10];
                        imm[7:6] = in_i[6:5];
                        imm[2:1] = in_i[4:3];
                        imm[5] = in_i[2];
                        imm[RegBits-1:8] = {(RegBits-8){in_i[12]}};
                        out_o = imm[12] << 32 | imm[10:5] << 25 | 5'b0 << 20 | rs1 << 15 || 3'b001 << 12 | imm[4:1] << 8 | imm[11] << 7 | 7'b1100011;
                    end  
                endcase
            end
            2'b10: begin
                pc_plus_2_o = 1'b1;
                rd = in_i[11:7];

                case(funct3)
                    3'b000: begin // C.SLLI
                        imm[4:0] = in_i[6:2];
                        out_o = imm[11:0] << 20 | rd << 15 | 3'b001 << 12 | rd << 7 | 7'b0010011;
                    end
                    3'b010: begin // C.LWSP
                        imm[5] = in_i[12];
                        imm[4:2] = in_i[6:4];
                        imm[7:6] = in_i[3:2];
                        out_o = imm[11:0] << 20 | 2'b10 << 15 | 3'b010 << 12 | rd << 7 | 7'b0000011;
                    end
                    3'b100: begin // C.JR/MV/JALR/ADD
                        if (in_i[12] == 1'b0) begin // C.JR/MV
                            if (in_i[6:2] == 5'b00000) begin // C.JR
                                rs2 = 'b0;
                                out_o = 12'b0 << 20 | rd << 15 | 3'b000 << 12 | 5'b00000 << 7 | 7'b1100111;
                            end else begin // C.MV
                                rs2 = in_i[6:2];
                                out_o = 7'b0 << 25 | rs2 << 20 | 5'b00000 << 15 | 3'b000 << 12 | rd << 7 | 7'b0110011; 
                            end
                        end else begin // C.JALR/ADD
                            if (in_i[6:2] == 5'b00000) begin // C.JALR
                                rs2 = 5'b00000;
                                out_o = 12'b0 << 20 | rd << 15 | 3'b000 << 12 | 5'b00001 << 7 | 7'b1100111;
                            end else begin // C.ADD
                                rs2 = in_i[6:2];
                                out_o = 7'b0 << 25 | rs2 << 20 | rd << 15 | 3'b000 << 12 | rd << 7 | 7'b0110011; 
                            end
                        end
                    end
                    3'b110: begin // C.SWSP
                        rs2 = in_i[6:2];
                        imm[5:2] = in_i[11:9];
                        imm[7:6] = in_i[8:7];
                        out_o = imm[11:5] << 25 | rs2 << 20 | 5'b00010 << 15 | 3'b010 << 12 | imm[4:0] << 7 | 7'b0100011; 
                    end
                endcase
            end
            2'b11: begin
                out_o = in_i;
                pc_plus_2_o = 1'b0;
            end
        endcase
    end

endmodule


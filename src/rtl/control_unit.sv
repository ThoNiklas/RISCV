/* verilator lint_off CASEINCOMPLETE */


module control_unit (
    input logic [6:0] op_i,
    input logic [2:0] funct3_i,
    input logic funct7_5_i,
    input logic [3:0] onzc_i,
    output logic  result_source_o, alu_source_o, reg_write_o,
    output logic [1:0] memory_write_o,
    output logic [1:0] pc_source_o, write_back_source_o,
    output logic [2:0] result_extend_control_o, immediate_source_o,
    output logic [3:0] alu_control_o
);

    logic [1:0] alu_op;
    
    alu_decoder alu_decoder (.alu_op_i(alu_op), .op_funct7_i({op_i[5],funct7_5_i}), .funct3_i(funct3_i), .alu_control_o(alu_control_o));

    pc_decoder pc_decoder (.op_i(op_i), .funct3_i(funct3_i), .onzc_i(onzc_i), .pc_source_o(pc_source_o));

    always_comb begin
        result_source_o = 1'b0;
        memory_write_o = 2'b000;
        alu_source_o = 1'b0;
        reg_write_o = 1'b0;
        write_back_source_o = 2'b00;
        result_extend_control_o = 3'b000;
        immediate_source_o = 3'b000;
        alu_op = 2'b00;

        case(op_i)
            7'b0110011: begin // R-Type
                reg_write_o = 1'b1;
                alu_op = 2'b10;
            end
            7'b0000011: begin // I-Type
                reg_write_o = 1'b1;
                alu_source_o = 1'b1;
                result_source_o = 1'b1;
                case(funct3_i)
                    3'b000: result_extend_control_o = 3'b001; // lb
                    3'b001: result_extend_control_o = 3'b010; // lh
                    3'b010: result_extend_control_o = 3'b000; // lw
                    3'b100: result_extend_control_o = 3'b101; // lbu
                    3'b101: result_extend_control_o = 3'b110; // lhu
                    default: result_extend_control_o = 3'b000;
                endcase
            end
            7'b0010011: begin // Immediate Instructions
                reg_write_o = 1'b1;
                alu_source_o = 1'b1;
                alu_op = 2'b10;
            end
            7'b1100111: begin // jalr
                reg_write_o = 1'b1;
                alu_source_o = 1'b1;
                alu_op = 2'b10;
                write_back_source_o = 2'b10;
            end
            7'b0010111: begin // auipc
                reg_write_o = 1'b1;
                immediate_source_o = 3'b011;
                alu_source_o = 1'b1;
                write_back_source_o = 2'b11;
            end
            7'b0110111: begin // lui
                reg_write_o = 1'b1;
                immediate_source_o = 3'b011;
                write_back_source_o = 2'b01;
            end
            7'b0100011: begin // S-Type
                immediate_source_o = 3'b001;
                alu_source_o = 1'b1;
                case(funct3_i)
                    3'b000: memory_write_o = 2'b01; // sb
                    3'b001: memory_write_o = 2'b10; // sh
                    3'b010: memory_write_o = 2'b11; // sw
                endcase
            end
            7'b1100011: begin // B-Type
                immediate_source_o = 3'b010;
                if (funct3_i[1] == 1'b0) alu_op = 2'b01; // signed
                else alu_op = 2'b11; // unsigned 
            end
            7'b1101111: begin // jal
                reg_write_o = 1'b1;
                immediate_source_o = 3'b100;
                write_back_source_o = 2'b10;
            end
            default: begin
                result_source_o = 1'b0;
                memory_write_o = 2'b00;
                alu_source_o = 1'b0;
                reg_write_o = 1'b0;
                write_back_source_o = 2'b00;
                result_extend_control_o = 3'b000;
                immediate_source_o = 3'b000;
                alu_op = 2'b00;
            end
        endcase
    end
endmodule


module ControlUnit (
    input logic [6:0] OP,
    input logic [2:0] Funct3,
    input logic Funct7_5,
    input logic [3:0] ONZC,
    output logic  ResultSrc, MemWrite, AluSrc, RegWrite,
    output logic [1:0] PCSrc, WriteBackSrc,
    output logic [2:0] ResultExtCtrl, ImmSrc,
    output logic [3:0] ALUControl
);

    logic [1:0] ALUOp;
    
    ALUDecoder aluDecoder (.ALUOp(ALUOp), .OPFunct7({OP[5],Funct7_5}), .Funct3(Funct3), .ALUControl(ALUControl));

    PCDecoder pcDecoder (.OP(OP), .Funct3(Funct3), .ONZC(ONZC), .PCSrc(PCSrc));

    always_comb begin
        ResultSrc = 1'b0;
        MemWrite = 1'b0;
        AluSrc = 1'b0;
        RegWrite = 1'b0;
        WriteBackSrc = 2'b00;
        ResultExtCtrl = 3'b000;
        ImmSrc = 3'b000;
        ALUOp = 2'b00;

        case(OP)
            7'b0110011: begin // R-Type
                RegWrite = 1'b1;
                ALUOp = 2'b10;
            end
            7'b0000011: begin // I-Type
                RegWrite = 1'b1;
                AluSrc = 1'b1;
                ResultSrc = 1'b1;
                case(Funct3)
                    3'b000: ResultExtCtrl = 3'b001; // lb
                    3'b001: ResultExtCtrl = 3'b010; // lh
                    3'b010: ResultExtCtrl = 3'b000; // lw
                    3'b100: ResultExtCtrl = 3'b101; // lbu
                    3'b101: ResultExtCtrl = 3'b110; // lhu
                    default: ResultExtCtrl = 3'b000;
                endcase
            end
            7'b0010011: begin // Immediate Instructions
                RegWrite = 1'b1;
                AluSrc = 1'b1;
                ALUOp = 2'b10;
            end
            7'b1100111: begin // jalr
                RegWrite = 1'b1;
                AluSrc = 1'b1;
                ALUOp = 2'b10;
                WriteBackSrc = 2'b10;
            end
            7'b0010111: begin // auipc
                RegWrite = 1'b1;
                ImmSrc = 3'b011;
                AluSrc = 1'b1;
                WriteBackSrc = 2'b11;
            end
            7'b0110111: begin // lui
                RegWrite = 1'b1;
                ImmSrc = 3'b011;
                WriteBackSrc = 2'b01;
            end
            7'b0100011: begin // S-Type
                ImmSrc = 3'b001;
                AluSrc = 1'b1;
                MemWrite = 1'b1;
            end
            7'b1100011: begin // B-Type
                ImmSrc = 3'b010;
                if (Funct3[1] == 1'b0) ALUOp = 2'b01; // signed
                else ALUOp = 2'b11; // unsigned 
            end
            7'b1101111: begin // jal
                RegWrite = 1'b1;
                ImmSrc = 3'b100;
                WriteBackSrc = 2'b10;
            end
            default: begin
                ResultSrc = 1'b0;
                MemWrite = 1'b0;
                AluSrc = 1'b0;
                RegWrite = 1'b0;
                WriteBackSrc = 2'b00;
                ResultExtCtrl = 3'b000;
                ImmSrc = 3'b000;
                ALUOp = 2'b00;
            end
        endcase
    end
endmodule


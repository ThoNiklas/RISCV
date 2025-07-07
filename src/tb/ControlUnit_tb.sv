module ControlUnit_tb (
    output logic  ResultSrc, MemWrite, AluSrc, RegWrite,
    output logic [1:0] PCSrc, WriteBackSrc,
    output logic [2:0] ResultExtCtrl, ImmSrc,
    output logic [3:0] ALUControl
);

    logic [6:0] OP;
    logic [2:0] Funct3;
    logic Funct7_5;
    logic [3:0] ONZC;

    ControlUnit dut (.OP(OP), .Funct3(Funct3), .Funct7_5(Funct7_5), .ONZC(ONZC), .ResultSrc(ResultSrc), .MemWrite(MemWrite), .AluSrc(AluSrc), .RegWrite(RegWrite), .PCSrc(PCSrc), .WriteBackSrc(WriteBackSrc), .ResultExtCtrl(ResultExtCtrl), .ImmSrc(ImmSrc), .ALUControl(ALUControl));

    initial begin
        $dumpfile("ControlUnit_tb.vcd");
        $dumpvars(0, ControlUnit_tb);

        OP = 7'b0000000;
        Funct3 = 3'b000;
        Funct7_5 = 1'b0;
        ONZC = 4'b0000;

        #5ns;

        // loads
        OP = 7'b0000011;
        //lb
        #1ns;

        if (RegWrite != 1'b1        |
            ImmSrc != 3'b000        | 
            AluSrc != 1'b1          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b1       | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0000   | 
            ResultExtCtrl != 3'b001 | 
            WriteBackSrc != 2'b00) 
                $display("lb is not correct.");

        #4ns;

        Funct3 = 3'b001; // lh

        #1ns;

        if (RegWrite != 1'b1        |
            ImmSrc != 3'b000        | 
            AluSrc != 1'b1          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b1       | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0000   | 
            ResultExtCtrl != 3'b010 | 
            WriteBackSrc != 2'b00) 
                $display("lh is not correct.");

        #4ns;
    
        Funct3 = 3'b010; // lh

        #1ns;

        if (RegWrite != 1'b1        |
            ImmSrc != 3'b000        | 
            AluSrc != 1'b1          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b1       | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0000   | 
            ResultExtCtrl != 3'b000 | 
            WriteBackSrc != 2'b00) 
                $display("lw is not correct.");

        #4ns;

        Funct3 = 3'b100; // lbu

        #1ns;

        if (RegWrite != 1'b1        |
            ImmSrc != 3'b000        | 
            AluSrc != 1'b1          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b1       | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0000   | 
            ResultExtCtrl != 3'b101 | 
            WriteBackSrc != 2'b00) 
                $display("lbu is not correct.");

        #4ns;

        Funct3 = 3'b101; // lhu

        #1ns;

        if (RegWrite != 1'b1        |
            ImmSrc != 3'b000        | 
            AluSrc != 1'b1          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b1       | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0000   | 
            ResultExtCtrl != 3'b110 | 
            WriteBackSrc != 2'b00) 
                $display("lhu is not correct.");

        #4ns;

        //Immediate
        OP = 7'b0010011;
        Funct3 = 3'b000; // addi

        #1ns;

        if (RegWrite != 1'b1        |
            ImmSrc != 3'b000        | 
            AluSrc != 1'b1          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b0       | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0000   | 
            ResultExtCtrl != 3'b000 | 
            WriteBackSrc != 2'b00) 
                $display("addi is not correct.");

        #4ns;

        Funct3 = 3'b001; // slli

        #1ns;

        if (RegWrite != 1'b1        |
            ImmSrc != 3'b000        | 
            AluSrc != 1'b1          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b0       | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0110   | 
            ResultExtCtrl != 3'b000 | 
            WriteBackSrc != 2'b00) 
                $display("slli is not correct.");

        #4ns;

        Funct3 = 3'b010; // slti

        #1ns;

        if (RegWrite != 1'b1        |
            ImmSrc != 3'b000        | 
            AluSrc != 1'b1          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b0       | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0101   | 
            ResultExtCtrl != 3'b000 | 
            WriteBackSrc != 2'b00) 
                $display("slti is not correct.");

        #4ns;

        Funct3 = 3'b011; //sltiu

        #1ns;

        if (RegWrite != 1'b1        |
            ImmSrc != 3'b000        | 
            AluSrc != 1'b1          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b0       | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0111   | 
            ResultExtCtrl != 3'b000 | 
            WriteBackSrc != 2'b00) 
                $display("sltiu is not correct.");

        #4ns;

        Funct3 = 3'b100; // xori

        #1ns;

        if (RegWrite != 1'b1        |
            ImmSrc != 3'b000        | 
            AluSrc != 1'b1          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b0       | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0100   | 
            ResultExtCtrl != 3'b000 | 
            WriteBackSrc != 2'b00) 
                $display("xori is not correct.");

        #4ns;

        Funct3 = 3'b101; //srli

        #1ns;

        if (RegWrite != 1'b1        |
            ImmSrc != 3'b000        | 
            AluSrc != 1'b1          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b0       | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b1000   | 
            ResultExtCtrl != 3'b000 | 
            WriteBackSrc != 2'b00) 
                $display("srli is not correct.");

        #4ns;

        Funct7_5 = 1'b1; // srai
         
        #1ns;

        if (RegWrite != 1'b1        |
            ImmSrc != 3'b000        | 
            AluSrc != 1'b1          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b0       | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b1001   | 
            ResultExtCtrl != 3'b000 | 
            WriteBackSrc != 2'b00) 
                $display("srai is not correct.");

        #4ns;

        Funct3 = 3'b110; // ori
        Funct7_5 = 1'b0;

        #1ns;

        if (RegWrite != 1'b1        |
            ImmSrc != 3'b000        | 
            AluSrc != 1'b1          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b0       | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0011   | 
            ResultExtCtrl != 3'b000 | 
            WriteBackSrc != 2'b00) 
                $display("ori is not correct.");

        #4ns;

        Funct3 = 3'b111; // andi
        
        #1ns;

        if (RegWrite != 1'b1        |
            ImmSrc != 3'b000        | 
            AluSrc != 1'b1          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b0       | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0010   | 
            ResultExtCtrl != 3'b000 | 
            WriteBackSrc != 2'b00) 
                $display("andi is not correct.");

        #4ns;

        OP = 7'b0010111; // auipc
         
        #1ns;

        if (RegWrite != 1'b1        |
            ImmSrc != 3'b011        | 
            AluSrc != 1'b1          | 
            MemWrite != 1'b0        | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0000   | 
            WriteBackSrc != 2'b11) 
                $display("auipc is not correct.");

        #4ns;

        OP = 7'b0100011; // S-Type
        Funct3 = 3'b000; // sb        

        #1ns;

        if (RegWrite != 1'b0        |
            ImmSrc != 3'b001        | 
            AluSrc != 1'b1          | 
            MemWrite != 1'b1        | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0000)    
                $display("sb is not correct.");

        #4ns;

        Funct3 = 3'b001; // sh

        #1ns;

        if (RegWrite != 1'b0        |
            ImmSrc != 3'b001        | 
            AluSrc != 1'b1          | 
            MemWrite != 1'b1        | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0000)
                $display("sh is not correct.");

        #4ns;


        Funct3 = 3'b010; // sw

        #1ns;

        if (RegWrite != 1'b0        |
            ImmSrc != 3'b001        | 
            AluSrc != 1'b1          | 
            MemWrite != 1'b1        | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0000)
                $display("sw is not correct.");

        #4ns;

        OP = 7'b0110011; // R-Type
        Funct3 = 3'b000;
        Funct7_5 = 1'b0; // add

        #1ns;

        if (RegWrite != 1'b1        |
            AluSrc != 1'b0          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b0       | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0000   | 
            ResultExtCtrl != 3'b000 | 
            WriteBackSrc != 2'b00) 
                $display("add is not correct.");

        #4ns;

        Funct7_5 = 1'b1; // sub

        #1ns;

        if (RegWrite != 1'b1        |
            AluSrc != 1'b0          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b0       | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0001   | 
            ResultExtCtrl != 3'b000 | 
            WriteBackSrc != 2'b00) 
                $display("sub is not correct.");

        #4ns;

        Funct3 = 3'b001; // sll
        Funct7_5 = 1'b0;

        #1ns;

        if (RegWrite != 1'b1        |
            AluSrc != 1'b0          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b0       | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0110   | 
            ResultExtCtrl != 3'b000 | 
            WriteBackSrc != 2'b00) 
                $display("sll is not correct.");

        #4ns;

        Funct3 = 3'b010; // slt

        #1ns;

        if (RegWrite != 1'b1        |
            AluSrc != 1'b0          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b0       | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0101   | 
            ResultExtCtrl != 3'b000 | 
            WriteBackSrc != 2'b00) 
                $display("slt is not correct.");

        #4ns;

        Funct3 = 3'b011; // sltu

        #1ns;

        if (RegWrite != 1'b1        |
            AluSrc != 1'b0          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b0       | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0111   | 
            ResultExtCtrl != 3'b000 | 
            WriteBackSrc != 2'b00) 
                $display("sltu is not correct.");

        #4ns;

        Funct3 = 3'b100; // xor

        #1ns;

        if (RegWrite != 1'b1        |
            AluSrc != 1'b0          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b0       | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0100   | 
            ResultExtCtrl != 3'b000 | 
            WriteBackSrc != 2'b00) 
                $display("xor is not correct.");

        #4ns;

        Funct3 = 3'b101; // srl

        #1ns;

        if (RegWrite != 1'b1        |
            AluSrc != 1'b0          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b0       | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b1000   | 
            ResultExtCtrl != 3'b000 | 
            WriteBackSrc != 2'b00) 
                $display("srl is not correct.");

        #4ns;

        Funct7_5 = 1'b1; // sra

        #1ns;

        if (RegWrite != 1'b1        |
            AluSrc != 1'b0          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b0       | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b1001   | 
            ResultExtCtrl != 3'b000 | 
            WriteBackSrc != 2'b00) 
                $display("sra is not correct.");

        #4ns;

        Funct3 = 3'b110; // or
        Funct7_5 = 1'b0;

        #1ns;

        if (RegWrite != 1'b1        |
            AluSrc != 1'b0          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b0       | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0011   | 
            ResultExtCtrl != 3'b000 | 
            WriteBackSrc != 2'b00) 
                $display("or is not correct.");

        #4ns;

        Funct3 = 3'b111; // and

        #1ns;

        if (RegWrite != 1'b1        |
            AluSrc != 1'b0          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b0       | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0010   | 
            ResultExtCtrl != 3'b000 | 
            WriteBackSrc != 2'b00) 
                $display("and is not correct.");

        #4ns;

        OP = 7'b0110111; // lui 
        Funct3 = 3'b000;
        Funct7_5 = 1'b0;

        #1ns;

        if (RegWrite != 1'b1        |
            ImmSrc != 3'b011        | 
            PCSrc != 2'b00          | 
            WriteBackSrc != 2'b01) 
                $display("lui is not correct.");

        #4ns;
        OP = 7'b1100011; // B-Type
        //beq, not fulfilled
        
        #1ns;

        if (RegWrite != 1'b0        |
            ImmSrc != 3'b010        | 
            AluSrc != 1'b0          | 
            MemWrite != 1'b0        | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0001)
                $display("beq (not fulfilled) is not correct.");

        #4ns;

        ONZC[1] = 1'b1; // beq, fulfilled

        #1ns;

        if (RegWrite != 1'b0        |
            ImmSrc != 3'b010        | 
            AluSrc != 1'b0          | 
            MemWrite != 1'b0        | 
            PCSrc != 2'b01          | 
            ALUControl != 4'b0001)
                $display("beq (fulfilled) is not correct.");

        #4ns;

        Funct3 = 3'b001; // bne, not fulfilled

        #1ns;

        if (RegWrite != 1'b0        |
            ImmSrc != 3'b010        | 
            AluSrc != 1'b0          | 
            MemWrite != 1'b0        | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0001)
                $display("bne (not fulfilled) is not correct.");

        #4ns;

        ONZC[1] = 1'b0; // bne, fulfilled

        #1ns;

        if (RegWrite != 1'b0        |
            ImmSrc != 3'b010        | 
            AluSrc != 1'b0          | 
            MemWrite != 1'b0        | 
            PCSrc != 2'b01          | 
            ALUControl != 4'b0001)
                $display("bne (fulfilled) is not correct.");

        #4ns;

        Funct3 = 3'b100; // blt, not fulfilled

        #1ns;

        if (RegWrite != 1'b0        |
            ImmSrc != 3'b010        | 
            AluSrc != 1'b0          | 
            MemWrite != 1'b0        | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0001)
                $display("blt (not fulfilled) is not correct.");

        #4ns;

        ONZC[2] = 1'b1; // blt, fulfilled

        #1ns;

        if (RegWrite != 1'b0        |
            ImmSrc != 3'b010        | 
            AluSrc != 1'b0          | 
            MemWrite != 1'b0        | 
            PCSrc != 2'b01          | 
            ALUControl != 4'b0001)
                $display("blt (fulfilled) is not correct.");

        #4ns;

        Funct3 = 3'b101; // bge, not fulfilled

        #1ns;

        if (RegWrite != 1'b0        |
            ImmSrc != 3'b010        | 
            AluSrc != 1'b0          | 
            MemWrite != 1'b0        | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b0001)
                $display("bge (not fulfilled) is not correct.");

        #4ns;

        ONZC[2] = 1'b0; // bge, fulfilled

        #1ns;

        if (RegWrite != 1'b0        |
            ImmSrc != 3'b010        | 
            AluSrc != 1'b0          | 
            MemWrite != 1'b0        | 
            PCSrc != 2'b01          | 
            ALUControl != 4'b0001)
                $display("bge (fulfilled) is not correct.");

        #4ns;

        Funct3 = 3'b110; // bltu, not fulfilled

        #1ns;

        if (RegWrite != 1'b0        |
            ImmSrc != 3'b010        | 
            AluSrc != 1'b0          | 
            MemWrite != 1'b0        | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b1010)
                $display("bltu (not fulfilled) is not correct.");

        #4ns;

        ONZC[3] = 1'b1; // bltu, fulfilled

        #1ns;

        if (RegWrite != 1'b0        |
            ImmSrc != 3'b010        | 
            AluSrc != 1'b0          | 
            MemWrite != 1'b0        | 
            PCSrc != 2'b01          | 
            ALUControl != 4'b1010)
                $display("bltu (fulfilled) is not correct.");

        #4ns;

        Funct3 = 3'b111; // bgeu, not fulfilled

        #1ns;

        if (RegWrite != 1'b0        |
            ImmSrc != 3'b010        | 
            AluSrc != 1'b0          | 
            MemWrite != 1'b0        | 
            PCSrc != 2'b00          | 
            ALUControl != 4'b1010)
                $display("bgeu (not fulfilled) is not correct.");

        #4ns;

        ONZC[3] = 1'b0; // fulfilled

        #1ns;

        if (RegWrite != 1'b0        |
            ImmSrc != 3'b010        | 
            AluSrc != 1'b0          | 
            MemWrite != 1'b0        | 
            PCSrc != 2'b01          | 
            ALUControl != 4'b1010)
                $display("bgeu (fulfilled) is not correct.");

        #4ns;

        OP = 7'b1100111; // jalr
        Funct3 = 3'b000;

        #1ns;

        if (RegWrite != 1'b1        |
            ImmSrc != 3'b000        | 
            AluSrc != 1'b1          | 
            MemWrite != 1'b0        | 
            ResultSrc != 1'b0       | 
            PCSrc != 2'b10          | 
            ALUControl != 4'b0000   | 
            ResultExtCtrl != 3'b000 | 
            WriteBackSrc != 2'b10) 
                $display("jalr is not correct.");

        #4ns;

        OP = 7'b1101111; // jal

        #1ns;

        if (RegWrite != 1'b1        |
            ImmSrc != 3'b100        | 
            MemWrite != 1'b0        | 
            PCSrc != 2'b01          | 
            WriteBackSrc != 2'b10) 
                $display("jal is not correct.");

        #4ns;

    end


endmodule


module ALUDecoder_tb (
    output logic [3:0] ALUControl
);

    logic [1:0] ALUOp, OPFunct7;
    logic [2:0] Funct3;

    ALUDecoder dut (.ALUOp(ALUOp), .OPFunct7(OPFunct7), .Funct3(Funct3), .ALUControl(ALUControl));

    initial begin
        $dumpfile("ALUDecoder_tb.vcd");
        $dumpvars(0, ALUDecoder_tb);
        ALUOp = 0;
        OPFunct7 = 0;
        Funct3 = 0;

        #5ns;

        ALUOp = 2'b00; // I/S/U-Type

        #5ns;

        ALUOp = 2'b01; // B-Type

        #5ns;

        ALUOp = 2'b10; // add

        #5ns;

        OPFunct7 = 2'b11; // sub

        #5ns

        Funct3 = 3'b001; // sll

        #5ns;

        Funct3 = 3'b010; // slt

        #5ns;

        Funct3 = 3'b011; // sltu

        #5ns;
        
        Funct3 = 3'b100; // xor

        #5ns;
        
        Funct3 = 3'b101; // sra

        #5ns;
        
        OPFunct7 = 2'b01; // srl

        #5ns;
        
        Funct3 = 3'b110; // or

        #5ns;
        
        Funct3 = 3'b111; // and

        #5ns;
    end

endmodule


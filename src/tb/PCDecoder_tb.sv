module PCDecoder_tb(
    output logic [1:0] PCSrc
);

    logic [6:0] OP;
    logic [2:0] Funct3;
    logic [3:0] ONZC;

    PCDecoder dut (.OP(OP), .Funct3(Funct3), .ONZC(ONZC), .PCSrc(PCSrc));

    initial begin
        $dumpfile("PCDecoder_tb.vcd");
        $dumpvars(0, PCDecoder_tb);

        OP = 7'b0000000; // PC + 4
        Funct3 = 3'b000;
        ONZC = 4'b0000;

        #5ns;

        OP = 7'b1000100; // jalr

        #5ns;

        OP = 7'b1001100; // jal

        #5ns;

        OP = 7'b1000000;
        Funct3 = 3'b000; // beq
        ONZC = 4'b0000;

        #5ns;

        ONZC = 4'b0010;

        #5ns;

        Funct3 = 3'b001; // bne

        #5ns;

        ONZC = 4'b0000;

        #5ns

        Funct3 = 3'b010; // blt

        #5ns;

        ONZC = 4'b0100;

        #5ns;

        Funct3 = 3'b101; // bge

        #5ns;

        ONZC = 4'b0000;

        #5ns;

        Funct3 = 3'b110; // bltu

        #5ns;

        ONZC = 4'b1000;

        #5ns;

        Funct3 = 3'b111; // bgeu

        #5ns;

        ONZC = 4'b0000;

        #5ns;

    end
endmodule


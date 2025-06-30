module ExtendImm_tb #(parameter REG_BITS=32)
(output logic [REG_BITS-1:0] Out);

    logic [24:0] In;
    logic [2:0] ImmSrc;

    ExtendImm #(.REG_BITS(REG_BITS)) dut (.In(In), .ImmSrc(ImmSrc), .Out(Out));

    initial begin
        $dumpfile("ExtendImm_tb.vcd");
        $dumpvars(0, ExtendImm_tb);
        In = 0;
        ImmSrc = 0;

        #5ns;

        ImmSrc = 3'b000; // I-Type
        In = 25'b1010101010101010101010100;

        #5ns;

        ImmSrc = 3'b001; // S-Type
        
        #5ns;

        ImmSrc = 3'b010; // B-Type

        #5ns;

        ImmSrc = 3'b011; // U-Type

        #5ns;

        ImmSrc = 3'b100; // J-Type

        #5ns;

    end
endmodule


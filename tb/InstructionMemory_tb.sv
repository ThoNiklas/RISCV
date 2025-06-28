module InstructionMemory_tb(output logic [31:0] rd);

    logic [31:0] a;

    InstructionMemory #(.REG_BITS(32)) dut (.a(a), .rd(rd));

    initial begin
        $dumpfile("InstructionMemory_tb.vcd");
        $dumpvars(0, InstructionMemory_tb);

        a = 'b0;

        for (int i = 0; i < 100; i++) begin
           #10ns;
           a = a + 1;
        end
    end
endmodule


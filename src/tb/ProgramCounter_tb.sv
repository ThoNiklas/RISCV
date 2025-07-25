module ProgramCounter_tb(output logic [31:0] pc);

    logic clk, rst;
    logic [31:0] pcNext;
    logic [31:0] check;

    ProgramCounter #(.REG_BITS(32)) dut (.clk(clk), .rst(rst), .pcNext(pcNext), .pc(pc));

    initial begin
        $dumpfile("programCounterTB.vcd");
        $dumpvars(0, ProgramCounter_tb);
        clk = 'b0;
        rst = 'b0;
        pcNext = 'b0;
        pc = 'b0;

        $display("Start Testbench ProgramCounter");

        #5ns;

        rst = 'b1;

        check = 'b0;
        for (int i = 0; i < 64; i++) begin
            if (clk == 0) begin
                pcNext = pcNext + 1;
                check = check + 1;
            end
            #5ns;
            clk =~ clk;
            #1ns;
            if (pc != check) $display("Error, pc: %x, check: %x", pc, check);
            #4ns;
            clk =~ clk;
        end
        $display("End Testbench ProgramCounter");
    end


endmodule


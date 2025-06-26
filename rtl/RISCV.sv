module RISCV #(parameter REG_BITS=32, parameter ADDR_BITS=5) 
(
    //input logic clk, rst
    output logic [31:0] pc
);

    //logic [REG_BITS-1:0] pcNext, pc, instrRD, rd1, rd2, memRD;

    logic clk, rst;
    logic [31:0] pcNext;
    ProgramCounter #(.REG_BITS(REG_BITS)) programCounter(.clk(clk), .rst(rst), .pcNext(pcNext), .pc(pc));

    initial begin
        pcNext = 'b0;
        clk = 'b0;
        rst = 'b1;
        for (int i = 0; i < 100; i++) begin
            #5ns;
            clk = !clk;
            if (!clk) pcNext = pcNext + 1;
        end
    end

    InstructionMemory #(.REG_BITS(REG_BITS)) instructionMemory(.a(pc), .rd(instrRD));

    RegisterFile #(.REG_BITS(REG_BITS), .ADDR_BITS(ADDR_BITS)) registerFile(.clk(clk), .rst(rst), .we3(1'b0), .a1(0), .a2(0), .a3(0), .wd3(0), .rd1(rd1), .rd2(rd2));

    DataMemory #(.REG_BITS(REG_BITS)) dataMemory(.a(0), .wd(0), .we(0), .rd(memRD));

endmodule


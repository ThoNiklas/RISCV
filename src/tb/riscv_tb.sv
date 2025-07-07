`include "config.svh"

module riscv_tb #(parameter RegBits=32, parameter AddrBits=5) (
    output logic clk
);

    logic rst;
`ifdef TB
    riscv #(.RegBits(RegBits), .AddrBits(AddrBits)) dut (.clk_i(clk), .rst_i(rst));
`else
    riscv #(.RegBits(RegBits), .AddrBits(AddrBits)) dut (.clk_i(clk), .rst_i(rst));
`endif

    initial begin
        $dumpfile("riscv_tb.vcd");
        $dumpvars(0, riscv_tb);
        rst = 0;
        clk = 0;

        #5ns;

        rst = 1;

        #5ns;

        clk =~ clk;

        #5ns;

        clk =~ clk;

        #5ns;

        clk =~ clk;

        #5ns;

        clk =~ clk;

        #5ns;

        clk =~ clk;

        #5ns;
    end

endmodule


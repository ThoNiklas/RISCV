module RegisterFile_tb
(output logic [31:0] rd1, rd2);

   logic clk, rst, we3;
   logic [4:0] a1, a2, a3;
   logic [31:0] wd3;

   RegisterFile #(.REG_BITS(32), .ADDR_BITS(5)) dut (.clk(clk), .rst(rst), .we3(we3), .a1(a1), .a2(a2), .a3(a3), .wd3(wd3), .rd1(rd1), .rd2(rd2));

   initial begin
       $dumpfile("registerFileTB.vcd");
       $dumpvars(0, RegisterFile_tb);
       clk = 0;
       rst = 0;
       we3 = 0;

       a1 = 5'b00000;
       a2 = 5'b00001;
       a3 = 5'b00000;
       wd3= 'b0;

       #5ns;

       rst = 1;
       clk = 1;

       #5ns;
       clk= 0;
       we3 = 1;
       wd3 = 13;

       #5ns;
       clk = 1;
       #5ns;
       clk = 0;
       a3 = 5'b00001;
       #5ns;
       clk = 1;
       #5ns;
   end
endmodule


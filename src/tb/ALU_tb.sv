module ALU_tb #(parameter REG_BITS=5)
(
    output logic [3:0] ONZC,
    output logic [REG_BITS-1:0] C
);
    
    logic [REG_BITS-1:0] A,B;
    logic [3:0] ctrl;

   ALU #(.REG_BITS(REG_BITS)) dut (.A(A), .B(B), .C(C), .ctrl(ctrl), .ONZC(ONZC));

   initial begin
       $dumpfile("ALU_tb.vcd");
       $dumpvars(0, ALU_tb);
       A = 0;
       B = 0;
       ctrl = 4'b0000; // add

       #5ns;

       A = 5;
       B = 5;

       #5ns;

       A = 5'b11110;
       B = 5'b00001;

       #5ns;

       B = 5'b00010;

       #5ns;

       A = 5'b01111;

       #5ns;

       ctrl = 4'b0001; // sub

       #5ns;

       ctrl = 4'b0010; // and

       #5ns;

       B = 5'b00001;
       ctrl = 4'b0011; // or

       #5ns;

       ctrl = 4'b0101; // slt
       A = 5'b00000;
       B = 5'b00001;

       #5ns;

       B = 5'b11111;

       #5ns;

       A = 5'b11010;
       B = 5'b00001;
       ctrl = 4'b0110; //sll

       #5ns;

       ctrl = 4'b0111; // sltu

       #5ns;

       ctrl = 4'b1000; // srl

       #5ns;

       A = 5'b10000;
       ctrl = 4'b1001; // sra

       #5ns;

       ctrl = 4'b1010; // subu
       A = 5'b1100;
       B = 5'b0001;

       #5ns;

       A = 5'b0001;
       B = 5'b1000;
       
       #5ns;

   end

endmodule


module ALU #(parameter REG_BITS=32)
(
    input logic [REG_BITS-1:0] A, B,
    input logic [3:0] ctrl,
    output logic [3:0] ONZC,
    output logic [REG_BITS-1:0] C 
);

   logic [REG_BITS:0] tmpResult;

   always_comb begin
       ONZC = 4'b0000;
       tmpResult = 0;
       case(ctrl)
           4'b0000: begin //add
                tmpResult = A + B;
                C = tmpResult[REG_BITS-1:0];
                ONZC[0] = tmpResult[REG_BITS];
                if (C == 0) ONZC[1] = 1;
                if (C[REG_BITS-1] == 1) ONZC[2] = 1; 
                if ((A[REG_BITS-1] == B[REG_BITS-1]) && (A[REG_BITS-1] != C[REG_BITS-1])) ONZC[3] = 1;
           end
           4'b0001:begin  //sub
                tmpResult = A - B;
                C = tmpResult[REG_BITS-1:0];
                ONZC[0] = tmpResult[REG_BITS];
                if (C == 0) ONZC[1] = 1;
                if (C[REG_BITS-1] == 1) ONZC[2] = 1; 
                if ((A[REG_BITS-1] == B[REG_BITS-1]) && (A[REG_BITS-1] != C[REG_BITS-1])) ONZC[3] = 1;
           end
           4'b0010: //and 
                C = A & B;
           4'b0011: //or
                C = A | B;
           4'b0100: //xor
                C = A ^ B;
           4'b0101: //slt
                if ($signed(A) < $signed(B)) C = 1;
                else C = 0;
           4'b0110: begin  //sll
                C = A << B[4:0];
           end
           4'b0111: //sltu
               if ($unsigned(A) < $unsigned(B)) C = 1;
               else C = 0;
           4'b1000: //srl
                C = A >> B[4:0];
           4'b1001: //sra
                C = $signed(A) >>> B[4:0];
           default:
                C = 'b0;
       endcase
   end

endmodule


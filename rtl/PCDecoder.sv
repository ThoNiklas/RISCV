/* verilator lint_off UNUSEDSIGNAL */
module PCDecoder (
    input logic [6:0] OP,
    input logic [2:0] Funct3,
    input logic [3:0] ONZC,
    output logic [1:0] PCSrc
);

    always_comb begin
       if (OP[6] == 1'b0) PCSrc = 2'b00; // PC = PC + 4
       else begin
            if (OP[3:2] == 2'b01) PCSrc = 2'b10; // jalr
            else if (OP[3:2] == 2'b11) PCSrc = 2'b01; //jal
            else begin
               case(Funct3)
                   3'b000: begin // beq
                       if (ONZC[1] == 1'b1) PCSrc = 2'b01;
                       else PCSrc = 2'b00;
                   end
                   3'b001: begin // bne
                       if (ONZC[1] == 1'b0) PCSrc = 2'b01;
                       else PCSrc = 2'b00;
                   end
                   3'b100: begin // blt
                       if (ONZC[2] == 1'b1) PCSrc = 2'b01;
                       else PCSrc = 2'b00;
                   end
                   3'b101: begin // bge
                       if (ONZC[2] == 1'b0) PCSrc = 2'b01;
                       else PCSrc = 2'b00;
                   end
                   3'b110: begin // bltu
                       if (ONZC[3] == 1'b1) PCSrc = 2'b01;
                       else PCSrc = 2'b00;
                   end
                   3'b111: begin // bgeu
                       if (ONZC[3] == 1'b0) PCSrc = 2'b01;
                       else PCSrc = 2'b00;
                   end
                   default: PCSrc = 2'b00;
               endcase
            end
       end
    end

endmodule


/* verilator lint_off UNUSEDSIGNAL */
module pc_decoder (
    input logic [6:0] op_i,
    input logic [2:0] funct3_i,
    input logic [3:0] onzc_i,
    output logic [1:0] pc_source_o
);

    always_comb begin
       if (op_i[6] == 1'b0) pc_source_o = 2'b00; // PC = PC + 4
       else begin
            if (op_i[3:2] == 2'b01) pc_source_o = 2'b10; // jalr
            else if (op_i[3:2] == 2'b11) pc_source_o = 2'b01; //jal
            else begin
               case(funct3_i)
                   3'b000: begin // beq
                       if (onzc_i[1] == 1'b1) pc_source_o = 2'b01;
                       else pc_source_o = 2'b00;
                   end
                   3'b001: begin // bne
                       if (onzc_i[1] == 1'b0) pc_source_o = 2'b01;
                       else pc_source_o = 2'b00;
                   end
                   3'b100: begin // blt
                       if (onzc_i[2] == 1'b1) pc_source_o = 2'b01;
                       else pc_source_o = 2'b00;
                   end
                   3'b101: begin // bge
                       if (onzc_i[2] == 1'b0) pc_source_o = 2'b01;
                       else pc_source_o = 2'b00;
                   end
                   3'b110: begin // bltu
                       if (onzc_i[3] == 1'b1) pc_source_o = 2'b01;
                       else pc_source_o = 2'b00;
                   end
                   3'b111: begin // bgeu
                       if (onzc_i[3] == 1'b0) pc_source_o = 2'b01;
                       else pc_source_o = 2'b00;
                   end
                   default: pc_source_o = 2'b00;
               endcase
            end
       end
    end

endmodule


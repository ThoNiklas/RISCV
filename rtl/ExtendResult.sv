module ExtendResult #(parameter REG_BITS=32)
(
    input logic [REG_BITS-1:0] In,
    input logic [2:0] ResultExtCtrl,
    output logic [REG_BITS-1:0] Out
);
    always_comb begin 
       case(ResultExtCtrl)
           3'b000:
               Out = In;
           3'b001:
               Out = {{24{In[7]}}, In[7:0]};
           3'b010:
               Out = {{16{In[7]}}, In[15:0]};
           3'b101:
               Out = {{24{1'b0}}, In[7:0]};
           3'b110:
               Out = {{16{1'b0}}, In[15:0]};
           default:
               Out = 'b0;
       endcase
    end

endmodule


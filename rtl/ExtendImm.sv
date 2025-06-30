module ExtendImm #(parameter REG_BITS=32)
(
    input logic [24:0] In,
    input logic [2:0] ImmSrc,
    output logic [REG_BITS-1:0] Out
);
    always_comb begin
        case(ImmSrc)
            3'b000:
                Out = {{20{In[24]}}, In[24:13]};
            3'b001:
                Out = {{20{In[24]}}, In[24:18], In[4:0]};
            3'b010:
                Out = {{20{In[24]}}, In[0], In[23:18], In[4:1], 1'b0};
            3'b011:
                Out = {In[24:5], {12{1'b0}}};
            3'b100:
                Out = {{12{In[24]}}, In[12:5], In[13], In[23:14], 1'b0};
            default:
                Out = 'b0;
        endcase
    end


endmodule


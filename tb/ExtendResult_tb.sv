module ExtendResult_tb #(parameter REG_BITS=32)
(
    output logic [REG_BITS-1:0] Out
);

    logic [REG_BITS-1:0] In;
    logic [2:0] ResultExtCtrl;

    ExtendResult #(.REG_BITS(REG_BITS)) dut (.In(In), .ResultExtCtrl(ResultExtCtrl), .Out(Out));

    initial begin
        $dumpfile("ExtendResult_tb.vcd");
        $dumpvars(0, ExtendResult_tb);

        In = {16{2'b10}};
        ResultExtCtrl = 3'b000;

        #5ns;

        ResultExtCtrl = 3'b001;

        #5ns;

        ResultExtCtrl = 3'b010;

        #5ns;

        ResultExtCtrl = 3'b101;

        #5ns;

        ResultExtCtrl = 3'b110;

        #5ns;
    end
endmodule


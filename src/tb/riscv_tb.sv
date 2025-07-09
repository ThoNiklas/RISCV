`include "config.svh"

module riscv_tb ();

    parameter int RegBits = 32;
    parameter int AddrBits = 5;

    logic clk, rst;

//    riscv #(.RegBits(RegBits), .AddrBits(AddrBits)) dut (.clk_i(clk),
//                                                         .rst_i(tb_if.rst),
//                                                         .instr_i(tb_if.instr),
//                                                         .pc_o(tb_if.pc),
//                                                         .pc_next_o(tb_if.pc_next),
//                                                         .write_back_o(tb_if.write_back),
//                                                         .register_a_o(tb_if.register_a),
//                                                         .register_b_o(tb_if.register_b),
//                                                         .source_b_o(tb_if.source_b),
//                                                         .alu_result_o(tb_if.alu_result),
//                                                         .alu_control_o(tb_if.alu_control),
//                                                         .onzc_o(tb_if.onzc),
//                                                         .memory_write_o(tb_if.memory_write),
//                                                         .read_data_o(tb_if.read_data),
//                                                         .result_o(tb_if.result),
//                                                         .result_extended_o(tb_if.result_extended),
//                                                         .result_extend_control_o(tb_if.result_extend_control),
//                                                         .pc_plus_4_o(tb_if.pc_plus_4),
//                                                         .pc_target_o(tb_if.pc_target),
//                                                         .immediate_extended_o(tb_if.immediate_extended),
//                                                         .immediate_source_o(tb_if.immediate_source),
//                                                         .write_back_source_o(tb_if.write_back_source),
//                                                         .pc_source_o(tb_if.pc_source),
//                                                         .reg_write_o(tb_if.reg_write),
//                                                         .alu_source_o(tb_if.alu_source),
//                                                         .result_source_o(tb_if.result_source));

//    i_program #(.RegBits(RegBits), .AddrBits(AddrBits)) tb (tb_if, rst);

    riscv #(.RegBits(RegBits), .AddrBits(AddrBits)) dut (.clk_i(clk), .rst_i(rst));    

    initial begin 
        $dumpfile("riscv_tb.vcd");
        $dumpvars(0, riscv_tb);
        rst = 1'b0;
        clk = 1'b1;
        #5ns;
        clk = ~clk;
        for (int i=0; i < 50; i++) begin
            #5ns;
            rst = 1'b1;
            clk = ~clk;
        end
    end

endmodule


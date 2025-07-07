`include "config.svh"

module riscv #(parameter RegBits=32, parameter AddrBits=5) 
(
`ifdef TB
    input logic [RegBits-1:0] instr_i,
    output logic [RegBits-1:0] pc_o, pc_next_o,
    output logic [RegBits-1:0] write_back_o, register_a_o, register_b_o,
    output logic [RegBits-1:0] source_b_o, alu_result_o,
    output logic [3:0] alu_control_o, onzc_o,
    output logic memory_write_o,
    output logic [RegBits-1:0] read_data_o,
    output logic [RegBits-1:0] result_o, result_extended_o,
    output logic [2:0] result_extend_control_o,
    output logic [RegBits-1:0] pc_plus_4_o, pc_target_o,
    output logic [RegBits-1:0] immediate_extended_o,
    output logic [2:0] immediate_source_o,
    output logic [1:0] write_back_source_o,
    output logic [1:0] pc_source_o,
    output logic reg_write_o, alu_source_o,
    output logic result_source_o,
`endif
    input logic clk_i, rst_i
);

`ifdef TB

`else
    logic [RegBits-1:0] instr;
    logic [RegBits-1:0] pc_next, pc;
    logic [RegBits-1:0] write_back, register_a, register_b;
    logic [RegBits-1:0] source_b, alu_result;
    logic [3:0] alu_control, onzc;
    logic memory_write;
    logic [RegBits-1:0] read_data;
    logic [RegBits-1:0] result, result_extended;
    logic [2:0] result_extend_control;
    logic [RegBits-1:0] pc_plus_4, pc_target;
    logic [RegBits-1:0] immediate_extended;
    logic [2:0] immediate_source;
    logic [1:0] write_back_source;
    logic [1:0] pc_source;
    logic reg_write, alu_source;
    logic result_source;
`endif


    program_counter #(.RegBits(RegBits)) program_counter (.clk_i(clk_i), 
                                                          .rst_i(rst_i), 
                                                          .pc_next_i(pc_next), 
                                                          .pc_o(pc)); 

    instruction_memory #(.RegBits(RegBits)) instruction_memory (.a_i(pc), 
                                                                .rd_o(instr));



    register_file #(.RegBits(RegBits), .AddrBits(AddrBits)) register_file (.clk_i(clk_i), 
                                                                           .rst_i(rst_i), 
                                                                           .we3_i(reg_write), 
                                                                           .a1_i(instr[19:15]), 
                                                                           .a2_i(instr[24:20]), 
                                                                           .a3_i(instr[11:7]), 
                                                                           .wd3_i(write_back), 
                                                                           .rd1_o(register_a), 
                                                                           .rd2_o(register_b));


    alu #(.RegBits(RegBits)) alu (.a_i(register_a), 
                                  .b_i(source_b),
                                  .ctrl_i(alu_control),
                                  .onzc_o(onzc),
                                  .c_o(alu_result));

    
    data_memory #(.RegBits(RegBits)) data_memory (.a_i(alu_result),
                                                  .wd_i(register_b),
                                                  .clk_i(clk_i),
                                                  .we_i(memory_write),
                                                  .rd_o(read_data));

                                                  


    extend_result #(.RegBits(RegBits)) extend_result (.in_i(result), 
                                                      .result_extend_control_i(result_extend_control), 
                                                      .out_o(result_extended));

    extend_immediate #(.RegBits(RegBits)) extend_immediate(.in_i(instr[31:7]), 
                                                           .immediate_source_i(immediate_source),
                                                           .out_o(immediate_extended));

    control_unit control_unit (.op_i(instr[6:0]),
                               .funct3_i(instr[14:12]),
                               .funct7_5_i(instr[30]),
                               .onzc_i(onzc),
                               .result_source_o(result_source),
                               .memory_write_o(memory_write),
                               .alu_source_o(alu_source),
                               .reg_write_o(reg_write),
                               .pc_source_o(pc_source),
                               .write_back_source_o(write_back_source),
                               .result_extend_control_o(result_extend_control),
                               .immediate_source_o(immediate_source),
                               .alu_control_o(alu_control));

    always_comb begin 

        pc_plus_4 = pc + 4; // plus 4 bytes but plus 1 for next array entry
        pc_target = pc + immediate_extended;

        case(pc_source)
            2'b00: pc_next = pc_plus_4;
            2'b01: pc_next = pc_target;
            2'b10: pc_next = result_extended;
            default: pc_next = 'b0;
        endcase 


        result = result_source ? read_data : alu_result;

        case(write_back_source)
            2'b00: write_back = result_extended;
            2'b01: write_back = immediate_extended;
            2'b10: write_back = pc_plus_4;
            2'b11: write_back = pc_target;
        endcase

        source_b = alu_source ? immediate_extended : register_b;


        
        
    end

   

endmodule


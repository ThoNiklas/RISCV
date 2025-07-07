interface interface_tb #(parameter RegBits=32) (input clk);
    logic rst, memory_write, reg_write, alu_source, result_source;
    logic [RegBits-1:0] instr, pc, pc_next, write_back, register_a, register_b, source_b, alu_result, read_data, result, result_extended, pc_plus_4, pc_target, immediate_extended;
    logic [3:0] alu_control, onzc;
    logic [2:0] result_extend_control, immediate_source;
    logic [1:0] write_back_source, pc_source;
        
    clocking cb @(posedge clk);
        input memory_write, 
            reg_write, 
            alu_source, 
            result_source, 
            pc, 
            pc_next, 
            write_back, 
            register_a, 
            register_b, 
            source_b, 
            alu_result, 
            read_data, 
            result, 
            result_extended, 
            pc_plus_4, 
            pc_target, 
            immediate_extended, 
            alu_control, 
            onzc, 
            result_extend_control, 
            immediate_source, 
            write_back_source, 
            pc_source;
        output rst, instr;
    endclocking

    modport tb (input clk, clocking cb);
    modport dut (input clk, input rst, input instr, 
                 output memory_write, 
                 output reg_write, 
                 output alu_source,
                 output result_source, 
                 output pc, 
                 output pc_next, 
                 output write_back, 
                 output register_a, 
                 output register_b, 
                 output source_b, 
                 output alu_result, 
                 output read_data, 
                 output result, 
                 output result_extended, 
                 output pc_plus_4, 
                 output pc_target, 
                 output immediate_extended, 
                 output alu_control, 
                 output onzc, 
                 output result_extend_control, 
                 output immediate_source, 
                 output write_back_source, 
                 output pc_source);
        
endinterface

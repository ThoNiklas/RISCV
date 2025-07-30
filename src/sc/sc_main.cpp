#include "Vriscv.h"
#include "RiscvMonitor.h"

using namespace sc_core;

int sc_main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    sc_clock clk{"clk", 10, SC_NS, 0.5, 5, SC_NS, false};
    sc_signal<bool> reg_write_sig;
    sc_signal<bool> alu_source_sig;
    sc_signal<bool> result_source_sig;
    sc_signal<bool> rst_sig;
    sc_signal<uint32_t> alu_control_sig; 
    sc_signal<uint32_t> immediate_extended_sig; 
    sc_signal<uint32_t> onzc_sig;
    sc_signal<uint32_t> memory_write_sig;
    sc_signal<uint32_t> result_extend_control_sig;
    sc_signal<uint32_t> immediate_source_sig;
    sc_signal<uint32_t> write_back_source_sig;
    sc_signal<uint32_t> pc_source_sig;
    sc_signal<uint32_t> instr_sig;
    sc_signal<uint32_t> pc_sig;
    sc_signal<uint32_t> pc_next_sig;
    sc_signal<uint32_t> write_back_sig;
    sc_signal<uint32_t> register_a_sig;
    sc_signal<uint32_t> register_b_sig;
    sc_signal<uint32_t> source_b_sig;
    sc_signal<uint32_t> alu_result_sig;
    sc_signal<uint32_t> read_data_sig;
    sc_signal<uint32_t> result_sig;
    sc_signal<uint32_t> result_extended_sig;
    sc_signal<uint32_t> pc_plus_4_sig;
    sc_signal<uint32_t> pc_target_sig;

    Vriscv* dut = new Vriscv{"dut"};
    dut->clk_i(clk);
    dut->reg_write_o(reg_write_sig);
    dut->alu_source_o(alu_source_sig);
    dut->result_source_o(result_source_sig);
    dut->rst_i(rst_sig);
    dut->alu_control_o(alu_control_sig);
    dut->immediate_extended_o(immediate_extended_sig);
    dut->onzc_o(onzc_sig);
    dut->memory_write_o(memory_write_sig);
    dut->result_extend_control_o(result_extend_control_sig);
    dut->immediate_source_o(immediate_source_sig);
    dut->write_back_source_o(write_back_source_sig);
    dut->pc_source_o(pc_source_sig);
    dut->instr_o(instr_sig);
    dut->pc_o(pc_sig);
    dut->pc_next_o(pc_next_sig);
    dut->write_back_o(write_back_sig);
    dut->register_a_o(register_a_sig);
    dut->register_b_o(register_b_sig);
    dut->source_b_o(source_b_sig);
    dut->alu_result_o(alu_result_sig);
    dut->read_data_o(read_data_sig);
    dut->result_o(result_sig);
    dut->result_extended_o(result_extended_sig);
    dut->pc_plus_4_o(pc_plus_4_sig);
    dut->pc_target_o(pc_target_sig);


    RiscvMonitor monitor("monitor");
    monitor.clk(clk);
    monitor.reg_write(reg_write_sig);
    monitor.alu_source(alu_source_sig);
    monitor.result_source(result_source_sig);
    monitor.rst(rst_sig);
    monitor.alu_control(alu_control_sig);
    monitor.immediate_extended(immediate_extended_sig);
    monitor.onzc(onzc_sig);
    monitor.memory_write(memory_write_sig);
    monitor.result_extend_control(result_extend_control_sig);
    monitor.immediate_source(immediate_source_sig);
    monitor.write_back_source(write_back_source_sig);
    monitor.pc_source(pc_source_sig);
    monitor.instr(instr_sig);
    monitor.pc(pc_sig);
    monitor.pc_next(pc_next_sig);
    monitor.write_back(write_back_sig);
    monitor.register_a(register_a_sig);
    monitor.register_b(register_b_sig);
    monitor.source_b(source_b_sig);
    monitor.alu_result(alu_result_sig);
    monitor.read_data(read_data_sig);
    monitor.result(result_sig);
    monitor.result_extended(result_extended_sig);
    monitor.pc_plus_4(pc_plus_4_sig);
    monitor.pc_target(pc_target_sig);

    sc_trace_file* trace_file = sc_create_vcd_trace_file(argv[1]);
    trace_file->set_time_unit(1, sc_core::SC_NS);
    sc_trace(trace_file, clk, "clock");
    sc_trace(trace_file, reg_write_sig, "register_write");
    sc_trace(trace_file, alu_source_sig, "alu_source");
    sc_trace(trace_file, result_source_sig, "result_source");
    sc_trace(trace_file, rst_sig, "reset");
    sc_trace(trace_file, alu_control_sig, "alu_control");
    sc_trace(trace_file, immediate_extended_sig, "immediate_extended");
    sc_trace(trace_file, onzc_sig, "onzc");
    sc_trace(trace_file, memory_write_sig, "memory_write");
    sc_trace(trace_file, result_extend_control_sig, "result_extend_control");
    sc_trace(trace_file, immediate_source_sig, "immediate_source");
    sc_trace(trace_file, write_back_source_sig, "write_back_source");
    sc_trace(trace_file, pc_source_sig, "pc_source");
    sc_trace(trace_file, instr_sig, "instr");
    sc_trace(trace_file, pc_sig, "pc");
    sc_trace(trace_file, pc_next_sig, "pc_next");
    sc_trace(trace_file, write_back_sig, "write_back");
    sc_trace(trace_file, register_a_sig, "register_a");
    sc_trace(trace_file, register_b_sig, "register_b");
    sc_trace(trace_file, source_b_sig, "source_b");
    sc_trace(trace_file, alu_result_sig, "alu_result");
    sc_trace(trace_file, read_data_sig, "read_data");
    sc_trace(trace_file, result_sig, "result");
    sc_trace(trace_file, result_extended_sig, "result_extended");
    sc_trace(trace_file, pc_plus_4_sig, "pc_plus_4");
    sc_trace(trace_file, pc_target_sig, "pc_target");

    sc_start(5, SC_NS);

    rst_sig.write(true);
    
    sc_start(100, SC_NS);

    sc_close_vcd_trace_file(trace_file);

    delete dut;
    return 0;
}


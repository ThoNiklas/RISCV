using namespace sc_core;

SC_MODULE(RiscvMonitor) {
    sc_in<bool> clk;
    sc_in<bool> reg_write;
    sc_in<bool> alu_source;
    sc_in<bool> result_source;
    sc_in<bool> rst;
    sc_in<uint32_t> alu_control;
    sc_in<uint32_t> immediate_extended;
    sc_in<uint32_t> onzc;
    sc_in<uint32_t> memory_write;
    sc_in<uint32_t> result_extend_control;
    sc_in<uint32_t> immediate_source;
    sc_in<uint32_t> write_back_source;
    sc_in<uint32_t> pc_source;
    sc_in<uint32_t> instr;
    sc_in<uint32_t> pc;
    sc_in<uint32_t> pc_next;
    sc_in<uint32_t> write_back;
    sc_in<uint32_t> register_a;
    sc_in<uint32_t> register_b;
    sc_in<uint32_t> source_b;
    sc_in<uint32_t> alu_result;
    sc_in<uint32_t> read_data;
    sc_in<uint32_t> result;
    sc_in<uint32_t> result_extended;
    sc_in<uint32_t> pc_plus_4;
    sc_in<uint32_t> pc_target;

    void monitor_proc() {
        std::cout << "hello" << std::endl;        
    }

    SC_CTOR(RiscvMonitor) {
        SC_METHOD(monitor_proc);
        sensitive << clk.neg();
    }
};

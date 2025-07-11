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
        uint32_t opcode = instr & 0x7F;
        uint32_t rs1, rs2, rd, funct3, funct7, imm;

        if (opcode == 3 || opcode == 19 || opcode == 103) { // I-type
            rs1 = (instr & ( 0x1F << 15)) >> 15;
            rd = (instr & ( 0x1F << 7 )) >> 7;
            funct3 = (instr & (0x7 << 12)) >> 12;
            imm = (instr & (0x3FFF << 20)) >> 20;
        } else if (opcode == 23 || opcode == 55) { // U-type
            rd = (instr & (0x1F << 7) >> 7);
            imm = instr & (0xFFFFF << 12);
        } else if (opcode == 35) { // S-type
            rs1 = (instr & (0x1F << 15) >> 15);
            rs2 = (instr & (0x1F << 20) >> 20);
            // todo immediate
        } else if (opcode == 51) { // R-type
            rd = (instr & (0x1F << 7) >> 7);
            rs1 = (instr & (0x1F << 15) >> 15);
            rs2 = (instr & (0x1F << 20) >> 20);
            funct3 = (instr & (0x7 << 12) >> 12);
            funct7 = (instr & (0x7F << 25) >> 25);
        } else if (opcode == 99) { // B-type
            rs1 = (instr & (0x1F << 15) >> 15);
            rs2 = (instr & (0x1F << 20) >> 20);
            funct3 = (instr & (0x7 << 12) >> 12);
            // todo immediate
        } else if (opcode == 111) { // J-type
            rd = (instr & (0x1F << 7) >> 7);
            // todo immediate
        }
    }

    SC_CTOR(RiscvMonitor) {
        SC_METHOD(monitor_proc);
        sensitive << clk.neg();
    }
};

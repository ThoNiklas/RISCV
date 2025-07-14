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

    uint32_t reg_file[32];
    uint32_t data_mem[1024];

    void monitor_proc() {
        uint32_t opcode = instr & 0x7F;
        uint32_t rs1, rs2, rd, funct3, funct7, imm;
        bool checked_signals = false;

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
            uint32_t upper_immediate = (instr & (0x7F << 25) >> 20);
            uint32_t lower_immediate = (instr & (0x1F << 7) >> 7);
            imm = upper_immediate + lower_immediate;
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
            imm = (instr & (0xFFFFF << 12));
        } else if (opcode == 111) { // J-type
            rd = (instr & (0x1F << 7) >> 7);
            uint32_t imm_20 = (instr & (0x1 << 31) >> 11);
            uint32_t imm_19_12 = (instr & (0xFF << 12));
            uint32_t imm_11 = (instr & (0x1 << 13) >> 2);
            uint32_t imm_10_1 = (instr & (0x3FF << 14) >> 13);
            imm = imm_20 + imm_19_12 + imm_11 + imm_10_1;
        }
    }

    bool check_i_type(uint32_t rd, uint32_t rs1, uint32_t rs2, uint32_t funct3, uint32_t funct7) {
        if (!reg_write) return false;
        if (alu_source) return false;
        if (result_source) return false;
        //alu_control;
        //immediate_extended;
        //onzc;
        //memory_write;
        //result_extend_control;
        //immediate_source;
        //write_back_source;
        //pc_source;
        //write_back;
        //register_a;
        //register_b;
        //alu_result;
        //read_data;
        //result;
        //result_extended;
        return false;
    }

    SC_CTOR(RiscvMonitor) {
        SC_METHOD(monitor_proc);
        sensitive << clk.neg();

        for (int i = 0; i < (sizeof(reg_file)/sizeof(reg_file[0])); i++) {
            reg_file[i] = 0;
        }

        for (int i = 0; i < (sizeof(data_mem)/sizeof(data_mem[0])); i++) {
            data_mem[i] = 0;
        }
    }
};

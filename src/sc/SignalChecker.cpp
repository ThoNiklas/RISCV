#include "SignalChecker.h"

SignalChecker::SignalChecker(bool reg_write,
                  bool alu_source,
                  bool result_source,
                  bool rst,
                  uint32_t alu_control,
                  uint32_t immediate_extended,
                  uint32_t onzc,
                  uint32_t memory_write,
                  uint32_t result_extend_control,
                  uint32_t immediate_source,
                  uint32_t write_back_source,
                  uint32_t pc_source,
                  uint32_t instr,
                  uint32_t pc,
                  uint32_t pc_next,
                  uint32_t write_back,
                  uint32_t register_a,
                  uint32_t register_b,
                  uint32_t source_b,
                  uint32_t alu_result,
                  uint32_t read_data,
                  uint32_t result,
                  uint32_t result_extended,
                  uint32_t pc_plus_4,
                  uint32_t pc_target) : 
        reg_write(reg_write),
        alu_source(alu_source),
        result_source(result_source),
        rst(rst),
        alu_control(alu_control),
        immediate_extended(immediate_extended),
        onzc(onzc),
        memory_write(memory_write),
        result_extend_control(result_extend_control),
        immediate_source(immediate_source),
        write_back_source(write_back_source),
        pc_source(pc_source),
        instr(instr),
        pc(pc),
        pc_next(pc_next),
        write_back(write_back),
        register_a(register_a),
        register_b(register_b),
        source_b(source_b),
        alu_result(alu_result),
        read_data(read_data),
        result(result),
        result_extended(result_extended),
        pc_plus_4(pc_plus_4),
        pc_target(pc_target) {}



    void SignalChecker::check_i_type(uint32_t opcode, uint32_t rd, uint32_t rs1, uint32_t funct3, uint32_t imm) {

    }

    void SignalChecker::check_r_type(uint32_t rd, uint32_t rs1, uint32_t rs2, uint32_t funct3, uint32_t funct7) {

    }

    void SignalChecker::check_b_type(uint32_t rs1, uint32_t rs2, uint32_t funct3, uint32_t imm) {

    }

    void SignalChecker::check_j_type(uint32_t rd, uint32_t imm) {

    }

    void SignalChecker::check_u_type(uint32_t opcode, uint32_t rd, uint32_t imm) {

    }

    void SignalChecker::check_s_type(uint32_t rs1, uint32_t rs2, uint32_t funct3, uint32_t imm) {

    }

    void SignalChecker::display_error() {

    }

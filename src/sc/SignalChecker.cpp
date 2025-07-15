#include "SignalChecker.h"
#include "ISA_helper.h"
#include <iostream>

using namespace std;

uint32_t SignalChecker::get_alu_control(uint32_t opcode, uint32_t funct3, uint32_t funct7) {
    bool op5_funct75 = (opcode & 0b0100000) && (funct7 & 0b0100000);
    if (opcode == Load  || opcode == Jalr || opcode == Store || opcode == Auipc) return 0b0000;
    else if (opcode == Branch) {
        if (funct3 <= 0b101) return Sub;
        else return Subu;
    } 
    else {
        switch(funct3) {
        case 0b000:
            if (!op5_funct75) return Add;
            else return Sub;
            break;
        case 0b001:
            return Sll;
            break;
        case 0b010:
            return Slt;
            break;
        case 0b011:
            return Sltu;
            break;
        case 0b100:
            return Xor;
            break;
        case 0b101:
            if (funct7 & 0b0100000) return Sra;
            else return Srl;
            break;
        case 0b110:
            return Or;
            break;
        case 0b111:
            return And;
            break;
        }
    }
return Invalid;
}

bool SignalChecker::is_correct() {
    if (
        signal_checks[reg_write_check] == incorrect ||
        signal_checks[alu_source_check] == incorrect ||
        signal_checks[result_source_check] == incorrect ||
        signal_checks[rst_check] == incorrect ||
        signal_checks[alu_control_check] == incorrect ||
        signal_checks[immediate_extended_check] == incorrect ||
        signal_checks[onzc_check] == incorrect ||
        signal_checks[memory_write_check] == incorrect ||
        signal_checks[result_extend_control_check] == incorrect ||
        signal_checks[immediate_source_check] == incorrect ||
        signal_checks[write_back_source_check] == incorrect ||
        signal_checks[pc_source_check] == incorrect ||
        signal_checks[instr_check] == incorrect ||
        signal_checks[pc_check] == incorrect ||
        signal_checks[pc_next_check] == incorrect ||
        signal_checks[write_back_check] == incorrect ||
        signal_checks[register_a_check] == incorrect ||
        signal_checks[register_b_check] == incorrect ||
        signal_checks[source_b_check] == incorrect ||
        signal_checks[alu_result_check] == incorrect ||
        signal_checks[read_data_check] == incorrect ||
        signal_checks[result_check] == incorrect ||
        signal_checks[result_extended_check] == incorrect ||
        signal_checks[pc_plus_4_check] == incorrect ||
        signal_checks[pc_target_check] == incorrect) return false;
    else return true;
}

uint32_t SignalChecker::get_result_extend_control(uint32_t funct3) {
    switch(funct3) {
        case 0b000: // lb
            return 0b001;
        case 0b001: // lh
            return 0b010;
        case 0b010: // lw
            return 0b000;
        case 0b100: // lbu
            return 0b101;
        case 0b101: // lwu
            return 0b110;
    }
    return 0b111;
}


uint32_t SignalChecker::simulate_alu_operation(uint32_t operation, uint32_t operand1, uint32_t operand2) {
    switch(operation) {
        case Add:
            return operand1 + operand2;
        case Sub:
            return int32_t(operand1) - int32_t(operand2);
        case And:
            return operand1 & operand2;
        case Or:
            return operand1 | operand2;
        case Xor:
            return operand1 ^ operand2;
        case Slt:
            if (int32_t(operand1) < int32_t(operand2)) return 0b1;
            else return 0b0;
        case Sll:
            return operand1 << operand2;
        case Sltu:
            if (operand1 < operand2) return 0b1;
            else return 0b0;
        case Srl:
            return operand1 >> operand2;
        case Sra:
            return int64_t(operand1) >> operand2;
        case Subu:
            return operand1 - operand2;
    }
    return 0b0;
}

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
        pc_target(pc_target) {

    for (int i = 0; i < SIGNAL_CHECKERS_NR; i++) {
       signal_checks[i] = not_used; 
    }
}


uint32_t SignalChecker::simulate_result_extender(uint32_t input, uint32_t control) {
    switch(control) {
        case 0b000:
            return input;
        case 0b001:
            return int32_t((input & 0xFF));
        case 0b010:
            return int32_t((input & 0xFFFF));
        case 0b101:
            return (input & 0xFF);
        case 0b110:
            return (input & 0xFFFF);
    }
    return 0;
}

void SignalChecker::check_i_type(uint32_t opcode, uint32_t rd, uint32_t rs1, uint32_t funct3, uint32_t imm, uint32_t data) {
   uint32_t alu_operation = get_alu_control(opcode, funct3, (imm & (0x7F << 5) >> 5));
   uint32_t load_extend_control = get_result_extend_control(funct3);
   switch(opcode) {
    case 3: // loads         
        signal_checks[pc_source_check] = (pc_source == 0b00) ? correct : incorrect;
        signal_checks[result_source_check] = (result_source == true) ? correct : incorrect;
        signal_checks[memory_write_check] = (memory_write == false) ? correct : incorrect;
        signal_checks[alu_control_check] = (alu_control == alu_operation) ? correct : incorrect;
        signal_checks[alu_source_check] = (alu_source == true) ? correct : incorrect;
        signal_checks[result_extend_control_check] = (result_extend_control == load_extend_control) ? correct : incorrect;
        signal_checks[write_back_source_check] = (write_back_source == 0b00) ? correct : incorrect;
        signal_checks[immediate_source_check] = (immediate_source == 0b000) ? correct : incorrect;
        signal_checks[reg_write_check] = (reg_write == true) ? correct : incorrect;
        signal_checks[register_a_check] = (register_a == rs1) ? correct : incorrect;
        signal_checks[source_b_check] = (source_b == imm) ? correct : incorrect;
        signal_checks[alu_result_check] = (alu_result == simulate_alu_operation(opcode, register_a, source_b)) ? correct : incorrect;
        signal_checks[result_check] = (result == data) ? correct : incorrect;
        signal_checks[result_extended_check] = (result_extended == simulate_result_extender(result, result_extend_control)) ? correct : incorrect;
        signal_checks[write_back_check] = (write_back == result_extended) ? correct : incorrect;
        signal_checks[pc_next_check] = (pc_next == pc_plus_4) ? correct : incorrect;
        break;
    case 19: // immediate operations
        signal_checks[pc_source_check] = (pc_source == 0b00) ? correct : incorrect;
        signal_checks[result_source_check] = (result_source == false)? correct : incorrect;
        signal_checks[memory_write_check] = (memory_write == false) ? correct : incorrect;
        signal_checks[alu_control_check] = (alu_operation == alu_control) ? correct : incorrect; 
        signal_checks[alu_source_check] = (alu_source == true) ? correct : incorrect;
        signal_checks[result_extend_control_check] = (result_extend_control == 0b000) ? correct : incorrect;
        signal_checks[write_back_source_check] = (write_back_source == 0b00) ? correct : incorrect;
        signal_checks[immediate_source_check] = (immediate_source == 0b000) ? correct : incorrect;
        signal_checks[reg_write_check] = (reg_write == true) ? correct : incorrect;
        signal_checks[register_a_check] = (register_a == rs1) ? correct : incorrect;
        signal_checks[source_b_check] = (source_b = imm) ? correct : incorrect;
        signal_checks[alu_result_check] = (alu_result == simulate_alu_operation(alu_operation, register_a, source_b)) ? correct : incorrect;
        signal_checks[result_check] = (result == alu_result) ? correct : incorrect;
        signal_checks[result_extended_check] = (result_extended == result) ? correct : incorrect;
        signal_checks[write_back_check] = (write_back == result) ? correct : incorrect;
        signal_checks[pc_next_check] = (pc_next == pc_plus_4) ? correct : incorrect;
        break;
    case 103: // jalr

        break;
} 
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
   if (is_correct()) cout << "Correct or unused" << endl;
   else cout << "Processor is incorrect in line: " << pc/4 << endl;
}



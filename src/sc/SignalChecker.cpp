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
        reg_write_check == incorrect ||
        alu_source_check == incorrect ||
        result_source_check == incorrect ||
        rst_check == incorrect ||
        alu_control_check == incorrect ||
        immediate_extended_check == incorrect ||
        onzc_check == incorrect ||
        memory_write_check == incorrect ||
        result_extend_control_check == incorrect ||
        immediate_source_check == incorrect ||
        write_back_source_check == incorrect ||
        pc_source_check == incorrect ||
        instr_check == incorrect ||
        pc_check == incorrect ||
        pc_next_check == incorrect ||
        write_back_check == incorrect ||
        register_a_check == incorrect ||
        register_b_check == incorrect ||
        source_b_check == incorrect ||
        alu_result_check == incorrect ||
        read_data_check == incorrect ||
        result_check == incorrect ||
        result_extended_check == incorrect ||
        pc_plus_4_check == incorrect ||
        pc_target_check == incorrect) return false;
    else return true;
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

        reg_write_check = not_used;
        alu_source_check = not_used;
        result_source_check = not_used;
        rst_check = not_used;
        alu_control_check = not_used;
        immediate_extended_check = not_used;
        onzc_check = not_used;
        memory_write_check = not_used;
        result_extend_control_check = not_used;
        immediate_source_check = not_used;
        write_back_source_check = not_used;
        pc_source_check = not_used;
        instr_check = not_used;
        pc_check = not_used;
        pc_next_check = not_used;
        write_back_check = not_used;
        register_a_check = not_used;
        register_b_check = not_used;
        source_b_check = not_used;
        alu_result_check = not_used;
        read_data_check = not_used;
        result_check = not_used;
        result_extended_check = not_used;
        pc_plus_4_check = not_used;
        pc_target_check = not_used;
}



void SignalChecker::check_i_type(uint32_t opcode, uint32_t rd, uint32_t rs1, uint32_t funct3, uint32_t imm) {
   uint32_t alu_operation = get_alu_control(opcode, funct3, (imm & (0x7F << 5) >> 5));
   switch(opcode) {
    case 3: // loads         
        break;
    case 19: // immediate operations
        pc_source_check = (pc_source == 0b00) ? correct : incorrect;
        result_source_check = (result_source == 0b0) ? correct : incorrect;
        memory_write_check = (memory_write == false) ? correct : incorrect;
        alu_control_check = (alu_operation == alu_control) ? correct : incorrect; 
        alu_source_check = (alu_source == true) ? correct : incorrect;
        result_extend_control_check = (result_extend_control == 0b000) ? correct : incorrect;
        write_back_source_check = (write_back_source == 0b00) ? correct : incorrect;
        immediate_source_check = (immediate_source == 0b000) ? correct : incorrect;
        reg_write_check = (reg_write == true) ? correct : incorrect;
        register_a_check = (register_a == rs1) ? correct : incorrect;
        source_b_check = (source_b = imm) ? correct : incorrect;
        alu_result_check = (alu_result == simulate_alu_operation(alu_operation, register_a, source_b)) ? correct : incorrect;
        result_check = (result == alu_result) ? correct : incorrect;
        result_extended_check = (result_extended == result) ? correct : incorrect;
        write_back_check = (write_back == result) ? correct : incorrect;
        pc_next_check = (pc_next == pc_plus_4) ? correct : incorrect;
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



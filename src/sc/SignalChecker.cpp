#include "SignalChecker.h"
#include "ISA_helper.h"
#include <iostream>

using namespace std;

std::string signal_checkers_names[SIGNAL_CHECKERS_NR] = {
    "reg_write_check",
    "alu_source_check",
    "result_source_check",
    "rst_check",
    "alu_control_check",
    "immediate_extended_check",
    "onzc_check",
    "memory_write_check",
    "result_extend_control_check",
    "immediate_source_check",
    "write_back_source_check",
    "pc_source_check",
    "instr_check",
    "pc_check",
    "pc_next_check",
    "write_back_check",
    "register_a_check",
    "register_b_check",
    "source_b_check",
    "alu_result_check",
    "read_data_check",
    "result_check",
    "result_extended_check",
    "pc_plus_4_check",
    "pc_target_check",
    "pc_plus_2_check",
    "instr_pre_check"
};

uint32_t SignalChecker::get_alu_control(uint32_t opcode, uint32_t funct3, uint32_t funct7) {
    bool op5_funct75 = (opcode & 0b0100000) && (funct7 & 0b0100000);
    if (opcode == OP_LOAD  || opcode == OP_JALR || opcode == OP_STORE || opcode == OP_AUIPC) return ALU_CONTROL_ADD;
    else if (opcode == OP_BRANCH) {
        if (funct3 == FUNCT3_BLTU || funct3 == FUNCT3_BGEU) return ALU_CONTROL_SUBU;
        else return ALU_CONTROL_SUB;
    } 
    else {
        switch(funct3) {
        case FUNCT3_ADD:
            if (!op5_funct75) return ALU_CONTROL_ADD;
            else return ALU_CONTROL_SUB;
            break;
        case FUNCT3_SLL:
            return ALU_CONTROL_SLL;
            break;
        case FUNCT3_SLT:
            return ALU_CONTROL_SLT;
            break;
        case FUNCT3_SLTU:
            return ALU_CONTROL_SLTU;
            break;
        case FUNCT3_XOR:
            return ALU_CONTROL_XOR;
            break;
        case FUNCT3_SRL:
            if (funct7 & 0b0100000) return ALU_CONTROL_SRA;
            else return ALU_CONTROL_SRL;
            break;
        case FUNCT3_OR:
            return ALU_CONTROL_OR;
            break;
        case FUNCT3_AND:
            return ALU_CONTROL_AND;
            break;
        }
    }
return ALU_CONTROL_INVALID;
}

uint32_t SignalChecker::get_pc_source(uint32_t opcode, uint32_t funct3) {
    if (!(opcode & 0x40)) return PC_SOURCE_PLUS_4;
    else {
        uint32_t op_tmp = (opcode & 0b1100) >> 2;
        switch(op_tmp) {
            case 0b00: {
                switch(funct3) {
                    case FUNCT3_BEQ: {
                        if (signals[onzc_sig] & ONZC_ZERO) return PC_SOURCE_TARGET;
                        else return PC_SOURCE_PLUS_4;
                    }
                    case FUNCT3_BNE: {
                        if (!(signals[onzc_sig] & ONZC_ZERO)) return PC_SOURCE_TARGET;
                        else return PC_SOURCE_PLUS_4;
                    }
                    case FUNCT3_BLT: {
                        if (signals[onzc_sig] & ONZC_NEGATIVE) return PC_SOURCE_TARGET;
                        else return PC_SOURCE_PLUS_4;
                    }
                    case FUNCT3_BGE: {
                        if (!(signals[onzc_sig] & ONZC_NEGATIVE)) return PC_SOURCE_TARGET;
                        else return PC_SOURCE_PLUS_4;
                    }
                    case FUNCT3_BLTU: {
                        if (signals[onzc_sig] & ONZC_NEGATIVE) return PC_SOURCE_TARGET;
                        else return PC_SOURCE_PLUS_4;
                    }
                    case FUNCT3_BGEU: {
                        if (!(signals[onzc_sig] & ONZC_NEGATIVE)) return PC_SOURCE_TARGET;
                        else return PC_SOURCE_PLUS_4;
                    }
                }
            }
            case 0b01: {
                if (funct3 == FUNCT3_JALR) return PC_SOURCE_RESULT; // jalr
                break;
            }
            case 0b10: {
                return PC_SOURCE_PLUS_4; // not used
                break;
            }
            case 0b11: {
                return PC_SOURCE_TARGET; // jal
                break;
            }
        }
    }
    return PC_SOURCE_PLUS_4;
}

bool SignalChecker::is_correct() {
    if (
        signal_checks[reg_write_sig] == incorrect ||
        signal_checks[alu_source_sig] == incorrect ||
        signal_checks[result_source_sig] == incorrect ||
        signal_checks[rst_sig] == incorrect ||
        signal_checks[alu_control_sig] == incorrect ||
        signal_checks[immediate_extended_sig] == incorrect ||
        signal_checks[onzc_sig] == incorrect ||
        signal_checks[memory_write_sig] == incorrect ||
        signal_checks[result_extend_control_sig] == incorrect ||
        signal_checks[immediate_source_sig] == incorrect ||
        signal_checks[write_back_source_sig] == incorrect ||
        signal_checks[pc_source_sig] == incorrect ||
        signal_checks[instr_sig] == incorrect ||
        signal_checks[pc_sig] == incorrect ||
        signal_checks[pc_next_sig] == incorrect ||
        signal_checks[write_back_sig] == incorrect ||
        signal_checks[register_a_sig] == incorrect ||
        signal_checks[register_b_sig] == incorrect ||
        signal_checks[source_b_sig] == incorrect ||
        signal_checks[alu_result_sig] == incorrect ||
        signal_checks[read_data_sig] == incorrect ||
        signal_checks[result_sig] == incorrect ||
        signal_checks[result_extended_sig] == incorrect ||
        signal_checks[pc_plus_4_sig] == incorrect ||
        signal_checks[pc_target_sig] == incorrect) return false;
    else return true;
}

uint32_t SignalChecker::get_result_extend_control(uint32_t funct3) {
    switch(funct3) {
        case FUNCT3_LB: 
            return RESULT_EXT_SIGNED_BYTE;
        case FUNCT3_LH: 
            return RESULT_EXT_SIGNED_HALF;
        case FUNCT3_LW: 
            return RESULT_EXT_NO;
        case FUNCT3_LBU: 
            return RESULT_EXT_UNSIGNED_BYTE;
        case FUNCT3_LHU: 
            return RESULT_EXT_UNSIGNED_HALF;
    }
    return RESULT_EXT_INVALID;
}


int32_t SignalChecker::simulate_alu_operation(uint32_t operation, int32_t operand1, int32_t operand2) {
    switch(operation) {
        case ALU_CONTROL_ADD:
            return operand1 + operand2;
        case ALU_CONTROL_SUB:
            return int32_t(operand1) - int32_t(operand2);
        case ALU_CONTROL_AND:
            return operand1 & operand2;
        case ALU_CONTROL_OR:
            return operand1 | operand2;
        case ALU_CONTROL_XOR:
            return operand1 ^ operand2;
        case ALU_CONTROL_SLT:
            if (int32_t(operand1) < int32_t(operand2)) return 0b1;
            else return 0b0;
        case ALU_CONTROL_SLL:
            return operand1 << operand2;
        case ALU_CONTROL_SLTU:
            if (operand1 < operand2) return 0b1;
            else return 0b0;
        case ALU_CONTROL_SRL:
            return operand1 >> operand2;
        case ALU_CONTROL_SRA:
            return int64_t(operand1) >> operand2;
        case ALU_CONTROL_SUBU:
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
                  uint32_t pc_target,
                  bool pc_plus_2,
                  uint32_t instr_pre) {

    signals[reg_write_sig] = reg_write;
    signals[alu_source_sig] = alu_source;
    signals[result_source_sig] = result_source;
    signals[rst_sig] = rst;
    signals[alu_control_sig] = alu_control;
    signals[immediate_extended_sig] = immediate_extended;
    signals[onzc_sig] = onzc;
    signals[memory_write_sig] = memory_write;
    signals[result_extend_control_sig] = result_extend_control;
    signals[immediate_source_sig] = immediate_source;
    signals[write_back_source_sig] = write_back_source;
    signals[pc_source_sig] = pc_source;
    signals[instr_sig] = instr;
    signals[pc_sig] = pc;
    signals[pc_next_sig] = pc_next;
    signals[write_back_sig] = write_back;
    signals[register_a_sig] = register_a;
    signals[register_b_sig] = register_b;
    signals[source_b_sig] = source_b;
    signals[alu_result_sig] = alu_result;
    signals[read_data_sig] = read_data;
    signals[result_sig] = result;
    signals[result_extended_sig] = result_extended;
    signals[pc_plus_4_sig] = pc_plus_4;
    signals[pc_target_sig] = pc_target;
    signals[pc_plus_2_sig] = pc_plus_2;
    signals[instr_pre_sig] = instr_pre;

    for (int i = 0; i < SIGNAL_CHECKERS_NR; i++) {
       signal_checks[i] = not_used; 
    }
}


uint32_t SignalChecker::simulate_result_extender(uint32_t input, uint32_t control) {
    switch(control) {
        case RESULT_EXT_NO:
            return input;
        case RESULT_EXT_SIGNED_BYTE: {
            if (input & 0x80) return (input | 0xFFFFFF00);
            else return (input & 0xFF);
        }
        case RESULT_EXT_SIGNED_HALF: {
            if (input & 0x8000) return (input | 0xFFFF0000);
            else return (input & 0xFFFF);
        }
        case RESULT_EXT_UNSIGNED_BYTE:
            return (input & 0xFF);
        case RESULT_EXT_UNSIGNED_HALF:
            return (input & 0xFFFF);
    }
    return 0;
}

void SignalChecker::check_i_type(uint32_t opcode, uint32_t rd, uint32_t rs1, uint32_t funct3, int32_t imm, uint32_t data) {
   uint32_t alu_operation = get_alu_control(opcode, funct3, (imm >> 5));
   uint32_t load_extend_control = get_result_extend_control(funct3);
   uint32_t extended_result = simulate_result_extender(signals[result_sig], signals[result_extend_control_sig]);
   switch(opcode) {
    case OP_LOAD:          
        signal_checks[pc_source_sig] = (signals[pc_source_sig] == 0b00) ? correct : incorrect;
        signal_checks[result_source_sig] = (signals[result_source_sig] == true) ? correct : incorrect;
        signal_checks[memory_write_sig] = (signals[memory_write_sig] == 0b00) ? correct : incorrect;
        signal_checks[alu_control_sig] = (signals[alu_control_sig] == alu_operation) ? correct : incorrect;
        signal_checks[alu_source_sig] = (signals[alu_source_sig] == true) ? correct : incorrect;
        signal_checks[result_extend_control_sig] = (signals[result_extend_control_sig] == load_extend_control) ? correct : incorrect;
        signal_checks[write_back_source_sig] = (signals[write_back_source_sig] == 0b00) ? correct : incorrect;
        signal_checks[immediate_source_sig] = (signals[immediate_source_sig] == 0b000) ? correct : incorrect;
        signal_checks[reg_write_sig] = (signals[reg_write_sig] == true) ? correct : incorrect;
        signal_checks[register_a_sig] = (signals[register_a_sig] == rs1) ? correct : incorrect;
        signal_checks[source_b_sig] = (signals[source_b_sig] == imm) ? correct : incorrect;
        signal_checks[alu_result_sig] = (signals[alu_result_sig] == simulate_alu_operation(opcode, signals[register_a_sig], signals[source_b_sig])) ? correct : incorrect;
        //signal_checks[result_sig] = (signals[result_sig] == data) ? correct : incorrect;
        signal_checks[result_extended_sig] = (signals[result_extended_sig] == extended_result) ? correct : incorrect;
        signal_checks[write_back_sig] = (signals[write_back_sig] == signals[result_extended_sig]) ? correct : incorrect;
        signal_checks[pc_next_sig] = (signals[pc_next_sig] == signals[pc_plus_4_sig]) ? correct : incorrect;
        break;
    case OP_IMMEDIATE:
        signal_checks[pc_source_sig] = (signals[pc_source_sig] == 0b00) ? correct : incorrect;
        signal_checks[result_source_sig] = (signals[result_source_sig] == false)? correct : incorrect;
        signal_checks[memory_write_sig] = (signals[memory_write_sig] == 0b00) ? correct : incorrect;
        signal_checks[alu_control_sig] = (alu_operation == signals[alu_control_sig]) ? correct : incorrect; 
        signal_checks[alu_source_sig] = (signals[alu_source_sig] == true) ? correct : incorrect;
        signal_checks[result_extend_control_sig] = (signals[result_extend_control_sig] == 0b000) ? correct : incorrect;
        signal_checks[write_back_source_sig] = (signals[write_back_source_sig] == 0b00) ? correct : incorrect;
        signal_checks[immediate_source_sig] = (signals[immediate_source_sig] == 0b000) ? correct : incorrect;
        signal_checks[reg_write_sig] = (signals[reg_write_sig] == true) ? correct : incorrect;
        signal_checks[register_a_sig] = (signals[register_a_sig] == rs1) ? correct : incorrect;
        signal_checks[source_b_sig] = (signals[source_b_sig] == imm) ? correct : incorrect;
        signal_checks[alu_result_sig] = (signals[alu_result_sig] == simulate_alu_operation(alu_operation, signals[register_a_sig], signals[source_b_sig])) ? correct : incorrect;
        signal_checks[result_sig] = (signals[result_sig] == signals[alu_result_sig]) ? correct : incorrect;
        signal_checks[result_extended_sig] = (signals[result_extended_sig] == signals[result_sig]) ? correct : incorrect;
        signal_checks[write_back_sig] = (signals[write_back_sig] == signals[result_sig]) ? correct : incorrect;
        signal_checks[pc_next_sig] = (signals[pc_next_sig] == signals[pc_plus_4_sig]) ? correct : incorrect;
        break;
    case OP_JALR: 
        signal_checks[pc_source_sig] = (signals[pc_source_sig] == 0b10) ? correct : incorrect;
        signal_checks[result_source_sig] = (signals[result_source_sig] == false)? correct : incorrect;
        signal_checks[memory_write_sig] = (signals[memory_write_sig] == false) ? correct : incorrect;
        signal_checks[alu_control_sig] = (alu_operation == signals[alu_control_sig]) ? correct : incorrect; 
        signal_checks[alu_source_sig] = (signals[alu_source_sig] == true) ? correct : incorrect;
        signal_checks[result_extend_control_sig] = (signals[result_extend_control_sig] == 0b000) ? correct : incorrect;
        signal_checks[write_back_source_sig] = (signals[write_back_source_sig] == 0b10) ? correct : incorrect;
        signal_checks[immediate_source_sig] = (signals[immediate_source_sig] == 0b000) ? correct : incorrect;
        signal_checks[reg_write_sig] = (signals[reg_write_sig] == true) ? correct : incorrect;
        signal_checks[register_a_sig] = (signals[register_a_sig] == rs1) ? correct : incorrect;
        signal_checks[source_b_sig] = (signals[source_b_sig] == imm) ? correct : incorrect;
        signal_checks[alu_result_sig] = (signals[alu_result_sig] == simulate_alu_operation(alu_operation, signals[register_a_sig], signals[source_b_sig])) ? correct : incorrect;
        signal_checks[result_sig] = (signals[result_sig] == signals[alu_result_sig]) ? correct : incorrect;
        signal_checks[result_extended_sig] = (signals[result_extended_sig] == signals[result_sig]) ? correct : incorrect;
        signal_checks[write_back_sig] = (signals[write_back_sig] == signals[pc_plus_4_sig]) ? correct : incorrect;
        signal_checks[pc_next_sig] = (signals[pc_next_sig] == signals[result_sig]) ? correct : incorrect;
        break;
} 
}

void SignalChecker::check_r_type(uint32_t opcode, uint32_t rd, uint32_t rs1, uint32_t rs2, uint32_t funct3, uint32_t funct7) {
   uint32_t alu_operation = get_alu_control(opcode, funct3, funct7);

   signal_checks[pc_source_sig] = (signals[pc_source_sig] == 0b00) ? correct : incorrect;
   signal_checks[result_source_sig] = (signals[result_source_sig] == false)? correct : incorrect;
   signal_checks[memory_write_sig] = (signals[memory_write_sig] == 0b00) ? correct : incorrect;
   signal_checks[alu_control_sig] = (alu_operation == signals[alu_control_sig]) ? correct : incorrect; 
   signal_checks[alu_source_sig] = (signals[alu_source_sig] == false) ? correct : incorrect;
   signal_checks[result_extend_control_sig] = (signals[result_extend_control_sig] == 0b000) ? correct : incorrect;
   signal_checks[write_back_source_sig] = (signals[write_back_source_sig] == 0b00) ? correct : incorrect;
   signal_checks[immediate_source_sig] = (signals[immediate_source_sig] == 0b000) ? correct : incorrect;
   signal_checks[reg_write_sig] = (signals[reg_write_sig] == true) ? correct : incorrect;
   signal_checks[register_a_sig] = (signals[register_a_sig] == rs1) ? correct : incorrect;
   signal_checks[source_b_sig] = (signals[source_b_sig] == rs2) ? correct : incorrect;
   signal_checks[alu_result_sig] = (signals[alu_result_sig] == simulate_alu_operation(alu_operation, signals[register_a_sig], signals[source_b_sig])) ? correct : incorrect;
   signal_checks[result_sig] = (signals[result_sig] == signals[alu_result_sig]) ? correct : incorrect;
   signal_checks[result_extended_sig] = (signals[result_extended_sig] == signals[result_sig]) ? correct : incorrect;
   signal_checks[write_back_sig] = (signals[write_back_sig] == signals[result_sig]) ? correct : incorrect;
   signal_checks[pc_next_sig] = (signals[pc_next_sig] == signals[pc_plus_4_sig]) ? correct : incorrect;
}

void SignalChecker::check_b_type(uint32_t opcode, uint32_t rs1, uint32_t rs2, uint32_t funct3, uint32_t imm) {
    uint32_t alu_operation = get_alu_control(opcode, funct3, 0b0);
    uint32_t pc_source = get_pc_source(opcode, funct3);

    signal_checks[pc_source_sig] = (signals[pc_source_sig] == pc_source) ? correct : incorrect;
    signal_checks[result_source_sig] = (signals[result_source_sig] == false)? correct : incorrect;
    signal_checks[memory_write_sig] = (signals[memory_write_sig] == 0b00) ? correct : incorrect;
    signal_checks[alu_control_sig] = (alu_operation == signals[alu_control_sig]) ? correct : incorrect; 
    signal_checks[alu_source_sig] = (signals[alu_source_sig] == false) ? correct : incorrect;
    signal_checks[result_extend_control_sig] = (signals[result_extend_control_sig] == 0b000) ? correct : incorrect;
    signal_checks[write_back_source_sig] = (signals[write_back_source_sig] == 0b00) ? correct : incorrect;
    signal_checks[immediate_source_sig] = (signals[immediate_source_sig] == 0b010) ? correct : incorrect;
    signal_checks[reg_write_sig] = (signals[reg_write_sig] == false) ? correct : incorrect;
    signal_checks[register_a_sig] = (signals[register_a_sig] == rs1) ? correct : incorrect;
    signal_checks[source_b_sig] = (signals[source_b_sig] == rs2) ? correct : incorrect;
    signal_checks[alu_result_sig] = (signals[alu_result_sig] == simulate_alu_operation(alu_operation, signals[register_a_sig], signals[source_b_sig])) ? correct : incorrect;
    signal_checks[result_sig] = (signals[result_sig] == signals[alu_result_sig]) ? correct : incorrect;
    signal_checks[result_extended_sig] = (signals[result_extended_sig] == signals[result_sig]) ? correct : incorrect;
    signal_checks[write_back_sig] = (signals[write_back_sig] == signals[result_sig]) ? correct : incorrect;
    //signal_checks[pc_next_sig] = (signals[pc_next_sig] == signals[result_sig]) ? correct : incorrect;
}

void SignalChecker::check_j_type(uint32_t opcode, uint32_t rd, uint32_t imm) {
    uint32_t pc_source = get_pc_source(opcode, 0b000);

    signal_checks[pc_source_sig] = (signals[pc_source_sig] == pc_source) ? correct : incorrect;
    //signal_checks[result_source_sig] = (signals[result_source_sig] == false)? correct : incorrect;
    //signal_checks[memory_write_sig] = (signals[memory_write_sig] == false) ? correct : incorrect;
    //signal_checks[alu_control_sig] = (alu_operation == signals[alu_control_sig]) ? correct : incorrect; 
    //signal_checks[alu_source_sig] = (signals[alu_source_sig] == false) ? correct : incorrect;
    //signal_checks[result_extend_control_sig] = (signals[result_extend_control_sig] == 0b000) ? correct : incorrect;
    //signal_checks[write_back_source_sig] = (signals[write_back_source_sig] == 0b00) ? correct : incorrect;
    signal_checks[immediate_source_sig] = (signals[immediate_source_sig] == 0b100) ? correct : incorrect;
    //signal_checks[reg_write_sig] = (signals[reg_write_sig] == true) ? correct : incorrect;
    //signal_checks[register_a_sig] = (signals[register_a_sig] == rs1) ? correct : incorrect;
    //signal_checks[source_b_sig] = (signals[source_b_sig] == rs2) ? correct : incorrect;
    //signal_checks[alu_result_sig] = (signals[alu_result_sig] == simulate_alu_operation(alu_operation, signals[register_a_sig], signals[source_b_sig])) ? correct : incorrect;
    //signal_checks[result_sig] = (signals[result_sig] == signals[alu_result_sig]) ? correct : incorrect;
    //signal_checks[result_extended_sig] = (signals[result_extended_sig] == signals[result_sig]) ? correct : incorrect;
    //signal_checks[write_back_sig] = (signals[write_back_sig] == signals[result_sig]) ? correct : incorrect;
    signal_checks[pc_next_sig] = (signals[pc_next_sig] == signals[pc_target_sig]) ? correct : incorrect;
}

void SignalChecker::check_u_type(uint32_t opcode, uint32_t rd, uint32_t imm) {
    uint32_t write_back_source = 0b0;
    uint32_t write_back = 0b0;

    if (opcode == OP_AUIPC) { 
        write_back_source = 0b11; 
        write_back = imm + signals[pc_sig];
    }
    else if (opcode == OP_LUI) { 
        write_back_source = 0b01; 
        write_back = imm;
    }

    
    signal_checks[pc_source_sig] = (signals[pc_source_sig] == 0b00) ? correct : incorrect;
    signal_checks[result_source_sig] = (signals[result_source_sig] == false)? correct : incorrect;
    signal_checks[memory_write_sig] = (signals[memory_write_sig] == 0b00) ? correct : incorrect;
    //signal_checks[alu_control_sig] = (alu_operation == signals[alu_control_sig]) ? correct : incorrect; 
    //signal_checks[alu_source_sig] = (signals[alu_source_sig] == false) ? correct : incorrect;
    signal_checks[result_extend_control_sig] = (signals[result_extend_control_sig] == 0b000) ? correct : incorrect;
    signal_checks[write_back_source_sig] = (signals[write_back_source_sig] == write_back_source) ? correct : incorrect;
    signal_checks[immediate_source_sig] = (signals[immediate_source_sig] == 0b011) ? correct : incorrect;
    signal_checks[reg_write_sig] = (signals[reg_write_sig] == true) ? correct : incorrect;
    //signal_checks[register_a_sig] = (signals[register_a_sig] == rs1) ? correct : incorrect;
    //signal_checks[source_b_sig] = (signals[source_b_sig] == rs2) ? correct : incorrect;
    //signal_checks[alu_result_sig] = (signals[alu_result_sig] == simulate_alu_operation(alu_operation, signals[register_a_sig], signals[source_b_sig])) ? correct : incorrect;
    signal_checks[result_sig] = (signals[result_sig] == signals[alu_result_sig]) ? correct : incorrect;
    signal_checks[result_extended_sig] = (signals[result_extended_sig] == signals[result_sig]) ? correct : incorrect;
    signal_checks[write_back_sig] = (signals[write_back_sig] == write_back) ? correct : incorrect;
    signal_checks[pc_next_sig] = (signals[pc_next_sig] == signals[pc_plus_4_sig]) ? correct : incorrect;
}

void SignalChecker::check_s_type(uint32_t rs1, uint32_t rs2, uint32_t funct3, uint32_t imm) {
    uint32_t memory_write = 0b0;
    if (funct3 == FUNCT3_SB) memory_write = 0b01; 
    else if (funct3 == FUNCT3_SH) memory_write = 0b10; 
    else if (funct3 == FUNCT3_SW) memory_write = 0b11; 

   signal_checks[pc_source_sig] = (signals[pc_source_sig] == 0b00) ? correct : incorrect;
   signal_checks[result_source_sig] = (signals[result_source_sig] == false)? correct : incorrect;
   signal_checks[memory_write_sig] = (signals[memory_write_sig] == memory_write) ? correct : incorrect;
   signal_checks[alu_control_sig] = (0b0000 == signals[alu_control_sig]) ? correct : incorrect; 
   signal_checks[alu_source_sig] = (signals[alu_source_sig] == true) ? correct : incorrect;
   signal_checks[result_extend_control_sig] = (signals[result_extend_control_sig] == 0b000) ? correct : incorrect;
   signal_checks[write_back_source_sig] = (signals[write_back_source_sig] == 0b00) ? correct : incorrect;
   signal_checks[immediate_source_sig] = (signals[immediate_source_sig] == 0b001) ? correct : incorrect;
   signal_checks[reg_write_sig] = (signals[reg_write_sig] == false) ? correct : incorrect;
   signal_checks[register_a_sig] = (signals[register_a_sig] == rs1) ? correct : incorrect;
   signal_checks[source_b_sig] = (signals[source_b_sig] == imm) ? correct : incorrect;
   signal_checks[alu_result_sig] = (signals[alu_result_sig] == simulate_alu_operation(0b0000, signals[register_a_sig], signals[source_b_sig])) ? correct : incorrect;
   signal_checks[result_sig] = (signals[result_sig] == signals[alu_result_sig]) ? correct : incorrect;
   signal_checks[result_extended_sig] = (signals[result_extended_sig] == signals[result_sig]) ? correct : incorrect;
   signal_checks[write_back_sig] = (signals[write_back_sig] == signals[result_sig]) ? correct : incorrect;
   signal_checks[pc_next_sig] = (signals[pc_next_sig] == signals[pc_plus_4_sig]) ? correct : incorrect;
}

void SignalChecker::check_compressed_instruction(uint32_t instr_pre, uint32_t instr) {
    if ((instr_pre & 0xFFFF) == 0) return;

    uint32_t instr_ext;
    uint32_t quadrant = instr_pre & 0b11;
    uint16_t funct3 = (instr_pre & (0x3 << 13))  >> 13;

    uint32_t imm = 0;
    uint32_t rd = 0;
    uint32_t rs1 = 0;
    uint32_t rs2 = 0;

    switch(quadrant) {
        case (0b00): {
            switch(funct3) {
                case(0b000): { // c.addi4spn
                    rd = ((instr_pre & (0x7 << 2)) >> 2) | 0x8;
                    imm = ((instr_pre & (0x3 << 11)) >> 7) | ((instr_pre & (0xF << 7)) >> 1) | ((instr_pre & (0x1 << 6)) >> 4) | ((instr_pre & (0x1 << 5)) >> 2);
                    instr_ext = (imm << 20) | (0b00010 << 15) | (0b000 << 12) | (rd << 7) | (0b0010011);
                    break; 
                }
                case(0b010): { // c.lw
                    rd = ((instr_pre & (0x7 << 2)) >> 2) | 0x8;
                    rs1 = ((instr_pre & (0x7 << 7)) >> 7) | 0x8;
                    imm = ((instr_pre & (0x7 << 10)) >> 7) | ((instr_pre & (0x1 << 6)) >> 4) | ((instr_pre & (0x1 << 5)) >> 1);
                    instr_ext = (imm << 20) | (rs1 << 15) | (0b010 << 12) | (rd << 7) | (0b0000011);
                    break;
                }
                case(0b110): { // c.sw
                    rs1 = ((instr_pre & (0x7 << 7)) >> 7) | 0x8;
                    rs2 = ((instr_pre & (0x7 << 2)) >> 2) | 0x8;
                    imm = ((instr_pre & (0x7 << 10)) >> 7) | ((instr_pre & (0x1 << 6)) >> 4) | ((instr_pre & (0x1 << 5)) >> 1);
                    instr_ext = ((imm & 0xFE0) << 25) | (rs2 << 20) | (rs1 << 15) | (0b010 << 12) | ((imm & 0x1F) << 7) | (0b0100011);
                    break;
                }
            }
            break;
        }
        case (0b01): {
            switch(funct3) {
                case(0b000): { // c.nop/addi
                    if ((instr_pre & 0xF80) == 0) { // c.nop
                        instr_ext = 0x33;
                    } else { // c.addi
                        rd = (instr_pre & (0x1F << 7)) >> 7;
                        imm = ((instr_pre & (0x1 << 12)) >> 7) | ((instr_pre & (0x1F << 2)) >> 2);
                        if ((imm & 0x20)) imm = imm | 0xFFFFFFC0;
                        instr_ext = (imm << 20) | (rd << 15) | (0b000 << 12) | (rd << 7) | (0b0010011);
                    }
                    break;
                }
                case(0b001): { // c.jal
                    break;
                }
                case(0b010): { // c.li
                    break;
                }
                case(0b011): { // c.addi16sp/lui
                    break;
                }
                case(0b100): { // c.srli/srai/andi/sub/xor/or/and
                    break;
                }
                case(0b101): { // c.j
                    break;
                }
                case(0b110): { // c.beqz
                    break;
                }
                case(0b111): { // c.bnez
                    break;
                }
            }
            break;
        }
        case (0b10): {
            switch(funct3) {
                case(0b000): { // c.slli
                    rd = (instr_pre & (0x1F << 7)) >> 7;
                    imm = (instr_pre & (0x1F << 2)) >> 2;
                    instr_ext = (imm << 20) | (rd << 15) | (0b001 << 12) | (rd << 7) | (0b0010011);
                    break;
                }
                case(0b010): { // c.lwsp
                    rd = (instr_pre & (0x1F << 7)) >> 7;
                    imm = ((instr_pre & (0x1 << 12)) >> 7) | ((instr_pre & (0x7 << 4)) >> 2) | ((instr_pre & (0x3 << 2)) << 4);
                    instr_ext = (imm << 20) | (0b00010 << 15) | (0b010 << 12) | (rd << 7) | (0b0000011);
                    break;
                }
                case(0b100): { // c.jr/mv/jalr/add
                    break;
                }
                case(0b110): { // c.swsp
                    rs2 = (instr_pre & (0x1F << 2)) >> 2;
                    imm = ((instr_pre & (0xF << 9)) >> 7) | ((instr_pre & (0x3 << 7)) >> 1);
                    instr_ext = ((imm & 0xFE0) << 25) | (rs2 << 20) | (0x00010 << 15) | (0b010 << 12) | ((imm & 0x1F) << 7) | (0b0100011);
                    break;
                }
            }
            break;
        }
        case (0b11): {
            instr_ext = instr_pre;
            break;
        }
    }
    signal_checks[instr_sig]  = (instr_ext == instr) ? correct : incorrect;

}

void SignalChecker::display_error() {
   if (is_correct()) return; //cout << "Correct or unused" << endl;
   else {
        cout << "Processor is incorrect in adress: " << signals[pc_sig] << endl;
        for (int i = 0; i < SIGNAL_CHECKERS_NR; i++) {
            if (signal_checks[i] == incorrect) {
                cout << "\t" << signal_checkers_names[i] << " is incorrect: Value : " << signals[i] << endl;
            }
        }
    }
}



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
};

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

uint32_t SignalChecker::get_pc_source(uint32_t opcode, uint32_t funct3) {
    if (!(opcode & 0x40)) return 0b00;
    else {
        uint32_t op_tmp = (opcode & 0b1100) >> 2;
        switch(op_tmp) {
            case 0b00: {
                switch(funct3) {
                    case 0b000: {
                        if (signals[onzc_sig] & 0b10) return 0b01;
                        else return 0b00;
                    }
                    case 0b001: {
                        if (!(signals[onzc_sig] & 0b10)) return 0b01;
                        else return 0b00;
                    }
                    case 0b100: {
                        if (signals[onzc_sig] & 0b100) return 0b01;
                        else return 0b00;
                    }
                    case 0b101: {
                        if (!(signals[onzc_sig] & 0b100)) return 0b01;
                        else return 0b00;
                    }
                    case 0b110: {
                        if (signals[onzc_sig] & 0b100) return 0b01;
                        else return 0b00;
                    }
                    case 0b111: {
                        if (!(signals[onzc_sig] & 0b100)) return 0b01;
                        else return 0b00;
                    }
                }
            }
            case 0b01: {
                if (funct3 == 0b000) return 0b10; // jalr
                break;
            }
            case 0b10: {
                return 0b00; // not used
                break;
            }
            case 0b11: {
                return 0b01; // jal
                break;
            }
        }
    }
    return 0b00;
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


int32_t SignalChecker::simulate_alu_operation(uint32_t operation, int32_t operand1, int32_t operand2) {
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
                  uint32_t pc_target) {

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

    for (int i = 0; i < SIGNAL_CHECKERS_NR; i++) {
       signal_checks[i] = not_used; 
    }
}


uint32_t SignalChecker::simulate_result_extender(uint32_t input, uint32_t control) {
    switch(control) {
        case 0b000:
            return input;
        case 0b001: {
            if (input & 0x80) return (input | 0xFFFFFF00);
            else return (input & 0xFF);
        }
        case 0b010: {
            if (input & 0x8000) return (input | 0xFFFF0000);
            else return (input & 0xFFFF);
        }
        case 0b101:
            return (input & 0xFF);
        case 0b110:
            return (input & 0xFFFF);
    }
    return 0;
}

void SignalChecker::check_i_type(uint32_t opcode, uint32_t rd, uint32_t rs1, uint32_t funct3, int32_t imm, uint32_t data) {
   uint32_t alu_operation = get_alu_control(opcode, funct3, (imm >> 5));
   uint32_t load_extend_control = get_result_extend_control(funct3);
   uint32_t extended_result = simulate_result_extender(signals[result_sig], signals[result_extend_control_sig]);
   switch(opcode) {
    case 3: // loads         
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
    case 19: // immediate operations
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
    case 103: // jalr
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

    if (opcode == 23) { // auipc
        write_back_source = 0b11; 
        write_back = imm + signals[pc_sig];
    }
    else if (opcode == 55) { // lui
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
    if (funct3 == 0b000) memory_write = 0b01; // sb
    else if (funct3 == 0b001) memory_write = 0b10; // sh
    else if (funct3 == 0b010) memory_write = 0b11; // sw

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

void SignalChecker::display_error() {
   if (is_correct()) cout << "Correct or unused" << endl;
   else {
        cout << "Processor is incorrect in adress: " << signals[pc_sig] << endl;
        for (int i = 0; i < SIGNAL_CHECKERS_NR; i++) {
            if (signal_checks[i] == incorrect) {
                cout << "\t" << signal_checkers_names[i] << " is incorrect: Value : " << signals[i] << endl;
            }
        }
    }
}



#include <cstdint>

typedef enum signal_type{
    incorrect,
    correct,
    not_used,
} signal_type;

typedef enum signal_checkers{
    reg_write_check,
    alu_source_check,
    result_source_check,
    rst_check,
    alu_control_check,
    immediate_extended_check,
    onzc_check,
    memory_write_check,
    result_extend_control_check,
    immediate_source_check,
    write_back_source_check,
    pc_source_check,
    instr_check,
    pc_check,
    pc_next_check,
    write_back_check,
    register_a_check,
    register_b_check,
    source_b_check,
    alu_result_check,
    read_data_check,
    result_check,
    result_extended_check,
    pc_plus_4_check,
    pc_target_check,
    SIGNAL_CHECKERS_NR
} signal_checkers;

class SignalChecker {
    public:
        bool reg_write;
        bool alu_source;
        bool result_source;
        bool rst;
        uint32_t alu_control;
        uint32_t immediate_extended;
        uint32_t onzc;
        uint32_t memory_write;
        uint32_t result_extend_control;
        uint32_t immediate_source;
        uint32_t write_back_source;
        uint32_t pc_source;
        uint32_t instr;
        uint32_t pc;
        uint32_t pc_next;
        uint32_t write_back;
        uint32_t register_a;
        uint32_t register_b;
        uint32_t source_b;
        uint32_t alu_result;
        uint32_t read_data;
        uint32_t result;
        uint32_t result_extended;
        uint32_t pc_plus_4;
        uint32_t pc_target;

    SignalChecker(bool reg_write,
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
                  uint32_t pc_target);

        void check_i_type(uint32_t opcode, uint32_t rd, uint32_t rs1, uint32_t funct3, uint32_t imm, uint32_t data);
        void check_r_type(uint32_t rd, uint32_t rs1, uint32_t rs2, uint32_t funct3, uint32_t funct7);
        void check_b_type(uint32_t rs1, uint32_t rs2, uint32_t funct3, uint32_t imm);
        void check_j_type(uint32_t rd, uint32_t imm);
        void check_u_type(uint32_t opcode, uint32_t rd, uint32_t imm);
        void check_s_type(uint32_t rs1, uint32_t rs2, uint32_t funct3, uint32_t imm);
        void display_error();

    private:
        signal_type signal_checks[SIGNAL_CHECKERS_NR];

        uint32_t get_alu_control(uint32_t opcode, uint32_t funct3, uint32_t funct7);
        uint32_t get_result_extend_control(uint32_t funct3);
        uint32_t simulate_alu_operation(uint32_t operation, uint32_t operand1, uint32_t operand2);
        uint32_t simulate_result_extender(uint32_t input, uint32_t control);
        bool is_correct();
};

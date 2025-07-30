#include <cstdint>
#include <string>

typedef enum signal_type{
    incorrect,
    correct,
    not_used,
} signal_type;

typedef enum signal_names{
    reg_write_sig,
    alu_source_sig,
    result_source_sig,
    rst_sig,
    alu_control_sig,
    immediate_extended_sig,
    onzc_sig,
    memory_write_sig,
    result_extend_control_sig,
    immediate_source_sig,
    write_back_source_sig,
    pc_source_sig,
    instr_sig,
    pc_sig,
    pc_next_sig,
    write_back_sig,
    register_a_sig,
    register_b_sig,
    source_b_sig,
    alu_result_sig,
    read_data_sig,
    result_sig,
    result_extended_sig,
    pc_plus_4_sig,
    pc_target_sig,
    SIGNAL_CHECKERS_NR
} signal_names;


class SignalChecker {
    public:
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

        void check_i_type(uint32_t opcode, uint32_t rd, uint32_t rs1, uint32_t funct3, int32_t imm, uint32_t data);
        void check_r_type(uint32_t opcode, uint32_t rd, uint32_t rs1, uint32_t rs2, uint32_t funct3, uint32_t funct7);
        void check_b_type(uint32_t opcode, uint32_t rs1, uint32_t rs2, uint32_t funct3, uint32_t imm);
        void check_j_type(uint32_t opcode, uint32_t rd, uint32_t imm);
        void check_u_type(uint32_t opcode, uint32_t rd, uint32_t imm);
        void check_s_type(uint32_t rs1, uint32_t rs2, uint32_t funct3, uint32_t imm);
        void display_error();

        int32_t signals[SIGNAL_CHECKERS_NR];
    private:
        signal_type signal_checks[SIGNAL_CHECKERS_NR];

        uint32_t get_alu_control(uint32_t opcode, uint32_t funct3, uint32_t funct7);
        uint32_t get_pc_source(uint32_t opcode, uint32_t funct3);
        uint32_t get_result_extend_control(uint32_t funct3);
        int32_t simulate_alu_operation(uint32_t operation, int32_t operand1, int32_t operand2);
        uint32_t simulate_result_extender(uint32_t input, uint32_t control);
        bool is_correct();
};

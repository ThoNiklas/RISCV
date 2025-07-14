#include <cstdint>

typedef enum signal_type{
    incorrect,
    correct,
    not_used,
} signal_type;

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

        void check_i_type(uint32_t opcode, uint32_t rd, uint32_t rs1, uint32_t funct3, uint32_t imm);
        void check_r_type(uint32_t rd, uint32_t rs1, uint32_t rs2, uint32_t funct3, uint32_t funct7);
        void check_b_type(uint32_t rs1, uint32_t rs2, uint32_t funct3, uint32_t imm);
        void check_j_type(uint32_t rd, uint32_t imm);
        void check_u_type(uint32_t opcode, uint32_t rd, uint32_t imm);
        void check_s_type(uint32_t rs1, uint32_t rs2, uint32_t funct3, uint32_t imm);
        void display_error();

    private:
        signal_type reg_write_check;
        signal_type alu_source_check;
        signal_type result_source_check;
        signal_type rst_check;
        signal_type alu_control_check;
        signal_type immediate_extended_check;
        signal_type onzc_check;
        signal_type memory_write_check;
        signal_type result_extend_control_check;
        signal_type immediate_source_check;
        signal_type write_back_source_check;
        signal_type pc_source_check;
        signal_type instr_check;
        signal_type pc_check;
        signal_type pc_next_check;
        signal_type write_back_check;
        signal_type register_a_check;
        signal_type register_b_check;
        signal_type source_b_check;
        signal_type alu_result_check;
        signal_type read_data_check;
        signal_type result_check;
        signal_type result_extended_check;
        signal_type pc_plus_4_check;
        signal_type pc_target_check;

        uint32_t get_alu_control(uint32_t opcode, uint32_t funct3, uint32_t funct7);
        uint32_t simulate_alu_operation(uint32_t operation, uint32_t operand1, uint32_t operand2);
        bool is_correct();
};

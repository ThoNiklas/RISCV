typedef enum signal_type{
    incorrect,
    correct,
    not_used,
} signal_type;

class SignalChecker {
    public:
        bool reg_write_in;
        bool alu_source_in;
        bool result_source_in;
        bool rst_in;
        uint32_t alu_control_in;
        uint32_t immediate_extended_in;
        uint32_t onzc_in;
        uint32_t memory_write_in;
        uint32_t result_extend_control_in;
        uint32_t immediate_source_in;
        uint32_t write_back_source_in;
        uint32_t pc_source_in;
        uint32_t instr_in;
        uint32_t pc_in;
        uint32_t pc_next_in;
        uint32_t write_back_in;
        uint32_t register_a_in;
        uint32_t register_b_in;
        uint32_t source_b_in;
        uint32_t alu_result_in;
        uint32_t read_data_in;
        uint32_t result_in;
        uint32_t result_extended_in;
        uint32_t pc_plus_4_in;
        uint32_t pc_target_in;

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
                      uint32_t pc_target) : 
        reg_write_in(reg_write),
        alu_source_in(alu_source),
        result_source_in(result_source),
        rst_in(rst),
        alu_control_in(alu_control),
        immediate_extended_in(immediate_extended),
        onzc_in(onzc),
        memory_write_in(memory_write),
        result_extend_control_in(result_extend_control),
        immediate_source_in(immediate_source),
        write_back_source_in(write_back_source),
        pc_source_in(pc_source),
        instr_in(instr),
        pc_in(pc),
        pc_next_in(pc_next),
        write_back_in(write_back),
        register_a_in(register_a),
        register_b_in(register_b),
        source_b_in(source_b),
        alu_result_in(alu_result),
        read_data_in(read_data),
        result_in(result),
        result_extended_in(result_extended),
        pc_plus_4_in(pc_plus_4),
        pc_target_in(pc_target) {};

    private:
        signal_type reg_write;
        signal_type alu_source;
        signal_type result_source;
        signal_type rst;
        signal_type alu_control;
        signal_type immediate_extended;
        signal_type onzc;
        signal_type memory_write;
        signal_type result_extend_control;
        signal_type immediate_source;
        signal_type write_back_source;
        signal_type pc_source;
        signal_type instr;
        signal_type pc;
        signal_type pc_next;
        signal_type write_back;
        signal_type register_a;
        signal_type register_b;
        signal_type source_b;
        signal_type alu_result;
        signal_type read_data;
        signal_type result;
        signal_type result_extended;
        signal_type pc_plus_4;
        signal_type pc_target;
};

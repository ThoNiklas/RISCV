#define ALU_CONTROL_ADD      0b0000
#define ALU_CONTROL_SUB      0b0001
#define ALU_CONTROL_AND      0b0010
#define ALU_CONTROL_OR       0b0011
#define ALU_CONTROL_XOR      0b0100
#define ALU_CONTROL_SLT      0b0101
#define ALU_CONTROL_SLL      0b0110
#define ALU_CONTROL_SLTU     0b0111
#define ALU_CONTROL_SRL      0b1000
#define ALU_CONTROL_SRA      0b1001
#define ALU_CONTROL_SUBU     0b1010
#define ALU_CONTROL_INVALID  0b1111

#define OP_LOAD         3
#define OP_IMMEDIATE    19
#define OP_AUIPC        23
#define OP_STORE        35
#define OP_REGISTER     51
#define OP_LUI          55
#define OP_BRANCH       99
#define OP_JALR         103
#define OP_JAL          111

#define FUNCT3_LB       0b000
#define FUNCT3_LH       0b001
#define FUNCT3_LW       0b010
#define FUNCT3_LBU      0b100
#define FUNCT3_LHU      0b101
#define FUNCT3_ADDI     0b000
#define FUNCT3_SLLI     0b001
#define FUNCT3_SLTI     0b010
#define FUNCT3_SLTIU    0b011
#define FUNCT3_XORI     0b100
#define FUNCT3_SRLI     0b101
#define FUNCT3_SRAI     0b101
#define FUNCT3_ORI      0b110
#define FUNCT3_ANDI     0b111

//#define FUNCT3_AUIPC

#define FUNCT3_SB       0b000
#define FUNCT3_SH       0b001
#define FUNCT3_SW       0b010

#define FUNCT3_ADD      0b000
#define FUNCT3_SUB      0b000
#define FUNCT3_SLL      0b001
#define FUNCT3_SLT      0b010
#define FUNCT3_SLTU     0b011
#define FUNCT3_XOR      0b100
#define FUNCT3_SRL      0b101
#define FUNCT3_SRA      0b101
#define FUNCT3_OR       0b110
#define FUNCT3_AND      0b111

//#define FUNCT3_LUI      

#define FUNCT3_BEQ      0b000
#define FUNCT3_BNE      0b001
#define FUNCT3_BLT      0b100
#define FUNCT3_BGE      0b101
#define FUNCT3_BLTU     0b110
#define FUNCT3_BGEU     0b111

#define FUNCT3_JALR     0b000

//#define FUNCT3_JAL      

#define PC_SOURCE_PLUS_4    0b00
#define PC_SOURCE_TARGET    0b01
#define PC_SOURCE_RESULT    0b10

#define ONZC_OVERFLOW   0b1000
#define ONZC_NEGATIVE   0b100
#define ONZC_ZERO       0b10
#define ONZC_CARRY      0b1

#define RESULT_EXT_NO               0b000
#define RESULT_EXT_SIGNED_BYTE      0b001
#define RESULT_EXT_SIGNED_HALF      0b010
#define RESULT_EXT_UNSIGNED_BYTE    0b101
#define RESULT_EXT_UNSIGNED_HALF    0b110
#define RESULT_EXT_INVALID          0b111

#include <cstdint>

typedef enum ALUControl {
    Add  = 0b0000,
    Sub  = 0b0001,
    And  = 0b0010,
    Or   = 0b0011,
    Xor  = 0b0100,
    Slt  = 0b0101,
    Sll  = 0b0110,
    Sltu = 0b0111,
    Srl  = 0b1000,
    Sra  = 0b1001,
    Subu = 0b1010,
    Invalid = 0b1111
} ALUControl;

typedef enum OPCode {
    Load = 3,
    Immediate = 19,
    Auipc = 23,
    Store = 35,
    Register = 51,
    Lui = 55,
    Branch = 99,
    Jalr = 103,
    Jal = 111
} OPCode;

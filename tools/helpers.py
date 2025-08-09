opcodes = {
    "lb": "0000011",
    "lh": "0000011",
    "lw": "0000011",
    "lbu": "0000011",
    "lhu": "0000011",
    "addi": "0010011",
    "slli": "0010011",
    "slti": "0010011",
    "sltiu": "0010011",
    "xori": "0010011",
    "srli": "0010011",
    "srai": "0010011",
    "ori": "0010011",
    "andi": "0010011",
    "auipc": "0010111",
    "sb": "0100011",
    "sh": "0100011",
    "sw": "0100011",
    "add": "0110011",
    "sub": "0110011",
    "sll": "0110011",
    "slt": "0110011",
    "sltu": "0110011",
    "xor": "0110011",
    "srl": "0110011",
    "sra": "0110011",
    "or": "0110011",
    "and": "0110011",
    "lui": "0110111",
    "beq": "1100011",
    "bne": "1100011",
    "blt": "1100011",
    "bge": "1100011",
    "bltu": "1100011",
    "bgeu": "1100011",
    "jalr": "1100111",
    "jal": "1101111",
    "c.addi4spn": "00",
    "c.lw": "00",
    "c.sw": "00",
    "c.nop": "01",
    "c.addi": "01",
    "c.jal": "01",
    "c.li": "01",
    "c.addi16sp": "01",
    "c.lui": "01",
    "c.srli": "01",
    "c.srai": "01",
    "c.andi": "01",
    "c.sub": "01",
    "c.xor": "01",
    "c.or": "01",
    "c.and": "01",
    "c.j": "01",
    "c.beqz": "01",
    "c.bnez": "01",
    "c.slli": "10",
    "c.lwsp": "10",
    "c.jr": "10",
    "c.mv": "10",
    "c.jalr": "10",
    "c.add": "10",
    "c.swsp": "10",
}

funct3s = {
    "lb": "000",
    "lh": "001",
    "lw": "010",
    "lbu": "100",
    "lhu": "101",
    "addi": "000",
    "slli": "001",
    "slti": "010",
    "sltiu": "011",
    "xori": "100",
    "srli": "101",
    "srai": "101",
    "ori": "110",
    "andi": "111",
    "sb": "000",
    "sh": "001",
    "sw": "010",
    "add": "000",
    "sub": "000",
    "sll": "001",
    "slt": "010",
    "sltu": "011",
    "xor": "100",
    "srl": "101",
    "sra": "101",
    "or": "110",
    "and": "111",
    "beq": "000",
    "bne": "001",
    "blt": "100",
    "bge": "101",
    "bltu": "110",
    "bgeu": "111",
    "jalr": "000",
    "c.addi4spn": "000",
    "c.lw": "010",
    "c.sw": "110",
    "c.nop": "000",
    "c.addi": "000",
    "c.jal": "001",
    "c.li": "010",
    "c.addi16sp": "011",
    "c.lui": "011",
    "c.srli": "100",
    "c.srai": "100",
    "c.andi": "100",
    "c.sub": "100",
    "c.xor": "100",
    "c.or": "100",
    "c.and": "100",
    "c.j": "101",
    "c.beqz": "110",
    "c.bnez": "111",
    "c.slli": "000",
    "c.lwsp": "010",
    "c.jr": "100",
    "c.mv": "100",
    "c.jalr": "100",
    "c.add": "100",
    "c.swsp": "110",
}

funct7s = {
    "slli": "0000000",
    "srli": "0000000",
    "srai": "0100000",
    "add": "0000000",
    "sub": "0100000",
    "sll": "0000000",
    "slt": "0000000",
    "sltu": "0000000",
    "xor": "0000000",
    "srl": "0000000",
    "sra": "0100000",
    "or": "0000000",
    "and": "0000000",
}

funct4s = {
    "c.jr": "1000",
    "c.mv": "1000",
    "c.jalr": "1001",
    "c.add": "1001",
}

funct6s = {
    "c.sub": "100011",
    "c.xor": "100011",
    "c.or": "100011",
    "c.and": "100011",
}

functs = {
    "c.sub": "00",
    "c.xor": "01",
    "c.or": "10",
    "c.and": "11",
}

i_types = (
    "lb",
    "lh",
    "lw",
    "lbu",
    "lhu",
    "addi",
    "slli",
    "slti",
    "sltiu",
    "xori",
    "srli",
    "srai",
    "ori",
    "andi",
    "jalr",
)

loads = (
    "lb",
    "lh",
    "lw",
    "lbu",
    "lhu",
)

u_types = (
    "auipc",
    "lui",
)

s_types = (
    "sb",
    "sh",
    "sw",
)

r_types = (
    "add",
    "sub",
    "sll",
    "slt",
    "sltu",
    "xor",
    "srl",
    "sra",
    "or",
    "and",
)

b_types = (
    "beq",
    "bne",
    "blt",
    "bge",
    "bltu",
    "bgeu",
)

j_types = "jal"

cr_types = (
    "c.jr",
    "c.jalr",
    "c.mv",
    "c.add",
)
ci_types = (
    "c.lwsp",
    "c.li",
    "c.lui",
    "c.addi",
    "c.addi16sp",
)

css_types = "c.swsp"

cl_types = "c.lw"

cs_types = (
    "c.sw",
    "c.and",
    "c.or",
    "c.xor",
    "c.sub",
)

cb_types = (
    "c.beqz",
    "c.bnez",
)

cj_types = (
    "c.j",
    "c.jal",
)

import sys

from helpers import (
    b_types,
    funct3s,
    funct7s,
    i_types,
    j_types,
    opcodes,
    r_types,
    s_types,
    u_types,
)

if __name__ == "__main__":
    input_file_path = sys.argv[1]
    output_file_path = sys.argv[2]

    with open(input_file_path) as input_file:
        for line in input_file:
            command = line.split()
            opcode = command[0]
            parameters = command[1].split(",")

            if opcode in i_types:
                registerd = parameters[0]
                registerd = int(registerd[1:])
                registerd = str(bin(registerd)[2:].zfill(5))

                register1 = parameters[1]
                register1 = int(register1[1:])
                register1 = str(bin(register1)[2:].zfill(5))

                immediate = int(parameters[2])
                immediate = str(bin(immediate)[2:].zfill(12))

                machine_code = (
                    immediate
                    + register1
                    + funct3s[opcode]
                    + registerd
                    + opcodes[opcode]
                )
            elif opcode in u_types:
                immediate = int(parameters[1])
                immediate = str(bin(immediate)[2:].zfill(20))

                registerd = parameters[0]
                registerd = int(registerd[1:])
                registerd = str(bin(registerd)[2:].zfill(5))

                machine_code = immediate + registerd + opcodes[opcode]
            elif opcode in s_types:
                print("s")
            elif opcode in r_types:
                print("r")
                registerd = parameters[0]
                registerd = int(registerd[1:])
                registerd = str(bin(registerd)[2:].zfill(5))

                register1 = parameters[1]
                register1 = int(register1[1:])
                register1 = str(bin(register1)[2:].zfill(5))

                register2 = parameters[2]
                register2 = int(register2[1:])
                register2 = str(bin(register2)[2:].zfill(5))

                machine_code = (
                    funct7s[opcode]
                    + register2
                    + register1
                    + funct3s[opcode]
                    + registerd
                    + opcodes[opcode]
                )
            elif opcode in b_types:
                print("b")
            elif opcode in j_types:
                print("j")

            binary_opcode = opcodes[opcode]
            binary_funct3 = funct3s["sll"]
            binary_funct7 = funct7s["sll"]

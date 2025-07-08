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

labels = {}


def catch_labels(file):
    address = 0
    with open(file) as input_file:
        for line in input_file:
            line = line.split(":")
            if len(line) == 2:
                labels[line[0]] = address
            address = address + 4
    print(labels)


def parse_line(line):
    line = line.replace(",", "")
    command = line.split()

    label = None
    opcode = None
    parameters = ()
    if len(command) == 0:
        return (label, opcode, parameters)

    if command[0][-1] == ":":  # label
        label = command[0][:-1]
        command = command[1:]

    opcode = command[0]

    if command[-2] == ";":  # comment
        command = command[:-2]

    opcode = command[0]
    command = command[1:]

    for param in command:
        if param[0] == "r":
            parameters = parameters + (int(param[1:]),)
        elif param[-1] != ")" and not param.isalpha():
            parameters = parameters + (int(param),)
        elif param.isalpha():
            parameters = parameters + (param,)
        elif param[-1] == ")":
            param = param.split("(")
            parameters = parameters + (
                int(param[1][1:-1]),
                int(param[0]),
            )

    print(label, opcode, parameters)

    return (label, opcode, parameters)


def dec_to_bin(n, bits):
    if n < 0:
        n = (1 << bits) + n  # two's complement for negative n
    return bin(n)[2:].zfill(bits)


input_file_path = sys.argv[1]
output_file_path = sys.argv[2]
address = 0
catch_labels(input_file_path)

output_file = open(output_file_path, "w")

with open(input_file_path) as input_file:
    for line in input_file:
        (label, opcode, parameters) = parse_line(line)
        if opcode is None:  # empty line
            continue
        if opcode in i_types:
            machine_code = (
                dec_to_bin(parameters[2], 12)
                + dec_to_bin(parameters[1], 5)
                + funct3s[opcode]
                + dec_to_bin(parameters[0], 5)
                + opcodes[opcode]
            )
        elif opcode in u_types:
            machine_code = (
                dec_to_bin(parameters[1], 32)[0:20]
                + dec_to_bin(parameters[0], 5)
                + opcodes[opcode]
            )
        elif opcode in s_types:
            immediate = dec_to_bin(parameters[2], 12)
            machine_code = (
                immediate[0:7]
                + dec_to_bin(parameters[1], 5)
                + dec_to_bin(parameters[0], 5)
                + funct3s[opcode]
                + immediate[7:12]
                + opcodes[opcode]
            )
        elif opcode in r_types:
            machine_code = (
                funct7s[opcode]
                + dec_to_bin(parameters[2], 5)
                + dec_to_bin(parameters[1], 5)
                + funct3s[opcode]
                + dec_to_bin(parameters[0], 5)
                + opcodes[opcode]
            )
        elif opcode in b_types:
            diff = labels[parameters[2]] - address
            immediate = dec_to_bin(diff, 13)
            machine_code = (
                immediate[0]
                + immediate[2:8]
                + dec_to_bin(parameters[1], 5)
                + dec_to_bin(parameters[0], 5)
                + funct3s[opcode]
                + immediate[8:13]
                + opcodes[opcode]
            )
        elif opcode in j_types:
            diff = labels[parameters[1]] - address
            immediate = dec_to_bin(diff, 21)
            machine_code = (
                immediate[0]
                + immediate[10:20]
                + immediate[9]
                + immediate[1:9]
                + dec_to_bin(parameters[0], 5)
                + opcodes[opcode]
            )
        address = address + 4
        print(machine_code, len(machine_code))
        output_file.write(machine_code + "\n")

output_file.close()

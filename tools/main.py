import sys

from helpers import *

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


input_file_path = sys.argv[1]

catch_labels(input_file_path)

with open(input_file_path) as input_file:
    for line in input_file:
        (label, opcode, parameters) = parse_line(line)
        if opcode is None:  # empty line
            continue
        if opcode in i_types:
            print("i")
            machine_code = (
                str(bin(parameters[2])[2:].zfill(12))
                + str(bin(parameters[1])[2:].zfill(5))
                + funct3s(opcode)
                + str(bin(parameters[0])[2:].zfill(5))
                + opcodes(opcode)
            )
        elif opcode in u_types:
            print("u")
        elif opcode in s_types:
            print("s")
        elif opcode in r_types:
            print("r")
        elif opcode in b_types:
            print("b")
        elif opcode in j_types:
            print("j")

        binary_opcode = opcodes[opcode]
        binary_funct3 = funct3s["sll"]
        binary_funct7 = funct7s["sll"]

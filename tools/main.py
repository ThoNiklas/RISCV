import re
import sys

from helpers import (
    b_types,
    cb_types,
    ci_types,
    cj_types,
    cl_types,
    cr_types,
    cs_types,
    css_types,
    funct3s,
    funct4s,
    funct6s,
    funct7s,
    functs,
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
            line_post = line.split(":")
            if len(line_post) == 2:
                labels[line_post[0]] = address
            check = re.search(r"c\.", line)
            if check:
                address = address + 2
            else:
                address = address + 4
    print(labels)


def parse_line(line):
    label = None
    opcode = None
    parameters = ()

    line_split = line.replace(",", "")
    command = line_split.split()

    if len(command) == 0:
        return (label, opcode, parameters)
    check = re.search(
        r"(([a-z]+:)?\s+)?[a-z]+\s+r([0-9]|1[0-9]|2[0-9]|3[0-1]),\s+"
        r"(\d+\(r([0-9]|1[0-9]|2[0-9]|3[0-1])\)|r([0-9]|1[0-9]|2[0-9]|3[0-1]),"
        r"\s\d+|r([0-9]|1[0-9]|2[0-9]|3[0-1]),\s+r([0-9]|1[0-9]|2[0-9]|3[0-1])"
        r"|\d+|r([0-9]|1[0-9]|2[0-9]|3[0-1]),\s+[a-zA-Z]+|[a-zA-Z]+)(\s+;.*)?",
        line,
    )
    if not check:
        print("Line Error in line: ", int(address / 4 + 1), "\n", line)
        exit()

    if command[0][-1] == ":":  # label
        label = command[0][:-1]
        command = command[1:]

    opcode = command[0]
    if opcode not in opcodes:
        print("Opcode not valid in line: ", int(address / 4) + 1, "\n", line)

    if ";" in command:  # comment
        index = command.index(";")
        command = command[:index]

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
            immediate = parameters[2]
            if opcode == "srai":
                immediate = immediate + 1024
            machine_code = (
                dec_to_bin(immediate, 12)
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
                + dec_to_bin(parameters[0], 5)
                + dec_to_bin(parameters[1], 5)
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
                + immediate[8:12]
                + immediate[1]
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
        elif opcode in cr_types:
            rs2 = "00000"
            if len(parameters) == 2:
                rs2 = dec_to_bin(parameters[1], 5)
            machine_code = (
                funct4s[opcode] + dec_to_bin(parameters[0], 5) + rs2 + opcodes[opcode]
            )
        elif opcode in ci_types:
            if opcode == "c.lwsp":
                immediate = dec_to_bin(parameters[1], 8)
                machine_code = (
                    funct3s[opcode]
                    + immediate[2]
                    + dec_to_bin(parameters[0], 5)
                    + immediate[3:6]
                    + immediate[0:2]
                    + opcodes[opcode]
                )
            elif opcode == "c.li" or opcode == "c.addi":
                immediate = dec_to_bin(parameters[1], 6)
                machine_code = (
                    funct3s[opcode]
                    + immediate[0]
                    + dec_to_bin(parameters[0], 5)
                    + immediate[1:6]
                    + opcodes[opcode]
                )
            elif opcode == "c.lui":
                immediate = dec_to_bin(parameters[1], 18)
                machine_code = (
                    funct3s[opcode]
                    + immediate[0]
                    + dec_to_bin(parameters[0], 5)
                    + immediate[1:6]
                    + opcodes[opcode]
                )
            elif opcode == "c.addi16sp":
                immediate = dec_to_bin(parameters[0], 10)
                machine_code = (
                    funct3s[opcode]
                    + immediate[0]
                    + "00010"
                    + immediate[5]
                    + immediate[3]
                    + immediate[1:3]
                    + immediate[4]
                    + opcodes[opcode]
                )

        elif opcode in css_types:
            immediate = dec_to_bin(parameters[1], 8)
            machine_code = (
                funct3s[opcode]
                + immediate[2:6]
                + immediate[0:2]
                + dec_to_bin(parameters[0], 5)
                + opcodes[opcode]
            )
        elif opcode in cl_types:
            immediate = dec_to_bin(parameters[1], 7)
            machine_code = (
                funct3s[opcode]
                + immediate[1:4]
                + dec_to_bin(parameters[2], 5)[2:5]
                + immediate[4]
                + immediate[0]
                + dec_to_bin(parameters[0], 5)[2:5]
                + opcodes[opcode]
            )
        elif opcode in cs_types:
            if opcode == "c.sw":
                immediate = dec_to_bin(parameters[2], 7)
                machine_code = (
                    funct3s[opcode]
                    + immediate[1:4]
                    + dec_to_bin(parameters[0])[2:5]
                    + immediate[4]
                    + immediate[0]
                    + dec_to_bin(parameters[1], 5)[2:5]
                    + opcodes[opcode]
                )
            else:
                machine_code = (
                    funct6s[opcode]
                    + dec_to_bin(parameters[0], 5)[2:5]
                    + functs[opcode]
                    + dec_to_bin(parameters[1], 5)[2:5]
                    + opcodes[opcode]
                )
        elif opcode in cb_types:
            immediate = dec_to_bin(parameters[1], 9)
            machine_code = (
                funct3s[opcode]
                + immediate[0]
                + immediate[4:6]
                + dec_to_bin(parameters[0], 5)[2:5]
                + immediate[1:3]
                + immediate[6:7]
                + immediate[3]
                + opcodes[opcode]
            )
        elif opcode in cj_types:
            immediate = dec_to_bin(parameters[0], 12)
            machine_code = (
                funct3s[opcode]
                + immediate[0]
                + immediate[8]
                + immediate[2:4]
                + immediate[1]
                + immediate[5]
                + immediate[4]
                + immediate[8:11]
                + immediate[6]
                + opcodes[opcode]
            )
        address = address + 4
        output_file.write(
            machine_code[24:32]
            + " "
            + machine_code[16:24]
            + " "
            + machine_code[8:16]
            + " "
            + machine_code[0:8]
            + "\n"
        )

output_file.close()

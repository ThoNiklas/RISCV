import sys


def read_file(filename):
    f = open(filename)
    return f.read()


if __name__ == "__main__":
    input_file_path = sys.argv[1]
    output_file_path = sys.argv[2]

    with open(input_file_path) as input_file:
        for line in input_file:
            command = line.split()
            opcode = command[0]
            parameters = command[1].split(",")
            print(opcode)
            print(parameters)

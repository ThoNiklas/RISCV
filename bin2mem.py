# bin2mem.py — for $readmemb
import sys

with open(sys.argv[1], "rb") as f:
    data = f.read()

# Pad to multiple of 4 bytes (32 bits)
while len(data) % 4 != 0:
    data += b"\x00"

for i in range(0, len(data), 4):
    word = int.from_bytes(data[i : i + 4], byteorder="little")  # little-endian
    print(f"{word:032b}")  # binary, 32 bits per line

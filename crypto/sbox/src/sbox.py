flag = "BEGINNER{w3_hav3_confusion_but_w3_n33d_diffu5i0n!!}"


def b_to_bin(b):
    res = ""
    for x in b:
        bits = bin(x)[2:]
        bits = "0" * (8 - len(bits)) + bits
        res += bits
    return res


sbox = {
    "000": "110",
    "001": "100",
    "010": "111",
    "011": "001",
    "100": "101",
    "101": "000",
    "110": "011",
    "111": "010",
}

b = b_to_bin(flag.encode())

assert len(b) % 3 == 0

for i in range(0, len(b), 3):
    part = b[i : (i + 3)]
    print(sbox[part], end="")

print()

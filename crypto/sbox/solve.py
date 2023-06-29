known = "BEGINNER{_________________________________________}"

chal = "111110101101111000110010111111111101010100100011111100111000100100010001001000011001100000001010001111110011110000011011100101011000010000101001001001011011010100101011001000111010100000000100001001011011010100001010001110101010111000011101111010011010001101011001111010011011010110011001100101011011111100001010001100110011101000101011001100101010111101011000001111111001110100000011100110111111110000010000"


def b_to_bin(b):
    res = ""
    for x in b:
        if x == "_":
            res += "????????"
        else:
            bits = bin(ord(x))[2:]
            bits = "0" * (8 - len(bits)) + bits
            res += bits
    return res


known_bits = b_to_bin(known)

assert len(known_bits) == len(chal)

sbox = {}

# Generate sbox
for i in range(0, len(chal), 3):
    k = known_bits[i : (i + 3)]

    if not "?" in k:
        sbox[chal[i : (i + 3)]] = k

# Decode challenge
print("Decrypted:")

for i in range(0, len(chal), 3):
    part = chal[i : (i + 3)]
    decoded = sbox[part]
    print(decoded, end="")

print()

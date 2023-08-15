# ancient_aliens

## Authors

- @CaptainBoggle


## Category
- crypto

## Description

WARNING!!! THIS CHALLENGE IS HARD (i think)!!!

We have been intercepting the alien communications, and it seems they are using an old, cryptographically insecure hashing function with constraints as a means of encrypting their messages...
Using the intercepted data, we have created a small testing program. Using the source code for this program, determine which input string will pass the checks in place. 

## Difficulty

- Hard



## Files
- [ancient_aliens.c](./_ctfd/files/ancient_aliens.c): TODO add description



## Solution

<details>
<summary>Spoiler</summary>

### Idea

Reverse the constrained CRC64 algorithm using symbolic execution.

### Walkthrough

# Method 1: KLEE
See solve.c for writeup.

# Method 2: MATHS???

From the source code, we see that a CRC algorithm is being used. CRC stands for "Cyclic Redundancy Check", which essentially performs polynomial division in GF(2) (a number system with only 0 and 1) with a divisor, and outputs the remainder from the process. The code performs CRC over three different divisors and checks them against three different remainders: our goal is to find the input string (the flag) which gives the required CRC outputs.

The CRC process treats each bit as a coefficient of an `x^k` term in the polynomial, and polynomial division is performed by left shifting our divisor to the position of the leftmost set bit and subtracting it using XOR (subtraction in GF(2) is just modulo 2 subtraction, which corresponds to XOR) until is longer (in bit length) than the input string number. One important point to note is that this code, unlike standard CRC, subtracts the divisor from the position after the leftmost set bit: we can make it equivalent to standard polynomial division by XORing each divisor with (`1 << 64`), since the set bit will be discarded from further calculations and the final remainder.

Now for the actually interesting part: the Chinese Remainder Theorem! Traditionally, its applied to find a number given some known integer congruences (where each congruence tells you a divisor and the remainder obtained from dividing the mystery number by it), or at least the remainder from the product of the divisors. It turns out the Chinese Remainder Theorem also applies to polynomials, and even better GF(2) polynomials! This is because this structure of objects falls into a mathematical classification called a "ring" (giving us properties like divisibility, coprimality, factors etc. essential for CRT).

Our attack is thus to use CRT to find the remainder for a large divisor, then bruteforce for the number whose string repr contains only alphanumeric characters (for simplicity we just check if the string starts with "BEG"). The code is below:

```python
# addition and subtraction (equivalent in mod 2) is XOR: ^
# we also define multiplication and division (div gives quotient, mod gives remainder)
def mult(x, y):
    s = 0
    for i in range(y.bit_length()):
        if y & (1 << i):
            s ^= x << i
    return s

def div(x, y): # x // y
    s = 0
    for i in range(x.bit_length() - 1, y.bit_length() - 2, -1):
        if x & (1 << i):
            x ^= (y << (i - y.bit_length() + 1))
            s ^= (1 << (i - y.bit_length() + 1))
    return s

#copy-paste :P
def mod(x, y): # x % y
    s = 0
    for i in range(x.bit_length() - 1, y.bit_length() - 2, -1):
        if x & (1 << i):
            x ^= (y << (i - y.bit_length() + 1))
            s ^= (1 << (i - y.bit_length() + 1))
    return x

def egcd(a, b): # first element is modular inverse of a in mod b
    if (b == 0):
        x = 1
        y = 0
        return (x, y, a)

    x1, y1, d = egcd(b, mod(a, b));
    x = y1;
    y = x1 ^ mult(y1, div(a, b));
    return (x, y, d)

def crt(congruences):
    M = 1
    for congruence in congruences:
        M = mult(M, congruence[1])

    solution = 0
    for congruence in congruences:
        a_i = congruence[0]
        M_i = div(M, congruence[1])
        N_i = egcd(M_i, congruence[1])[0]
        solution = mod(solution ^ (mult(mod(mult(a_i, M_i), M), N_i)), M)

    return solution

m1 = 0x42f0e1eba9ea3693 ^ (1 << 64)
m2 = 0xad93d23594c935a9 ^ (1 << 64)
m3 = 0x1337C0DE15BAAAAD ^ (1 << 64)
m4 = 0b10000000 # trick to make our program run faster by asserting the string ends with a closing brace

a1 = 0x8d264fc84bbeede9
a2 = 0x714ceac2d7a3aaa8
a3 = 0x780486b31ee4df55
a4 = ord("}")

# moduli aren't coprime, so divide out 5
m1 = div(m1, 5)
a1 = mod(a1, m1)

assert egcd(m1, m2)[2] == 1
assert egcd(m2, m3)[2] == 1
assert egcd(m3, m1)[2] == 1

solution = crt([(a1, m1), (a2, m2), (a3, m3), (a4, m4)])

assert(mod(solution, m1) == a1 and mod(solution, m2) == a2 and mod(solution, m3) == a3 and mod(solution, 5) == 0 and mod(solution, m4) == a4)

# now bruteforce for a number whose string repr starts with "BEG"
beginning = bin(ord("B"))[2:] + bin(ord("E"))[2:].zfill(8) + bin(ord("G"))[2:].zfill(8)
m = mult(mult(mult(m1, m2), m3), m4)
for i in range(1000):
    n = solution ^ mult(m, i)
    if bin(n)[2:].startswith(beginning):
        print(n) # convert to binary, pad with zeroes and chuck this guy into a binary to text translator: https://www.convertbinary.com/to-text/
        break
```
### Flag

`BEGINNER{iM_noT_reDUnDanT}`

</details>

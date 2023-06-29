# SBox

## Authors

- @ssparrow

## Category

- Crypto

## Description

Learn about S-Boxes here: [https://en.wikipedia.org/wiki/S-box](https://en.wikipedia.org/wiki/S-box)
The SBox in this challenge maps strings of 3 bits to other strings of 3 bits.
The flag for this challenge is encrypted below. Can you decode it?

`111110101101111000110010111111111101010100100011111100111000100100010001001000011001100000001010001111110011110000011011100101011000010000101001001001011011010100101011001000111010100000000100001001011011010100001010001110101010111000011101111010011010001101011001111010011011010110011001100101011011111100001010001100110011101000101011001100101010111101011000001111111001110100000011100110111111110000010000`

## Hints

1. The flag starts with the ascii text `BEGINNER{`

## Solution

<details>
<summary>Spoiler</summary>

### Idea

As we know the S-Box is a mapping from 3 bits to 3 bits, we can use the known plaintext "BEGINNER" to retrieve the S-Box state and decrypt the flag.

### Walkthrough

1. Doing your own research you should be able to find out how an S-Box works.
   Essentially, for this case, we convert the string to ASCII and map every 3
   bits into another 3 bits. Each 3 bit segment will always map to the same
   other 3 bit segment, so this process is reversable (in math you would call this
   a 1 to 1 function)
2. We know some of the characters (BEGINNER{}), so we can use this to find some of the
   3 bit to 3 bit mappings. This in fact gives us all the possible mappings, so then
   we can reverse this mapping to get the flag. I wrote a python script for this, see
   [solve.py](./solve.py)

### Flag

`BEGINNER{w3_hav3_confusion_but_w3_n33d_diffu5i0n!!}`

</details>

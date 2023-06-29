# Stream Cipher (PART 2)

## Authors

- @Baking2Trees

## Category

- Crypto

## Description

This is part 2 of the stream cipher challenge.

You have retrieved the ciphertext from earlier in such a short time that your partner is still skeptical of your skills. Hence, he dares you to recover the encryption's secret key before forming a team. To make it more challenging, he gives you a set of possible keys to choose from. You would like to take up the challenge and prove your cryptography prowess by cracking the code.

## Difficulty

- Easy

## Hints

1. The properties and operation of the XOR cipher can help you recover the key.
2. A One-time pad encryption aka. a Vernam cipher is used for the key stream. Hence, the key stream length may be a significant factor in the challenge.
3. The brute-force attack technique may be useful for this circumstance.
4. Wrap your answer in BEGINNER{} before submitting your flag.

## Files

- cipherText2.txt
- keyStreamsList.txt

Try include a link to the file where possible (such as within a repo).

## Solution

<details>
<summary>Spoiler</summary>

### Idea

Build upon the idea of Stream Cipher Challenge (PART 1).

This challenge explores the different stream cipher algorithm with a focus on the key stream.

Visit these sites to learn more about stream ciphers:

- "Handbook of Applied Cryptography" by Alfred J. Menezes, Paul C. van Oorschot, and Scott A. Vanstone, Chapter 6: http://cacr.uwaterloo.ca/hac/
- Securing Stream Ciphers (HMAC) - Computerphile: https://youtu.be/wlSG3pEiQdc
- XOR bitwise operation: https://www.khanacademy.org/computing/computer-science/cryptography/ciphers/a/xor-bitwise-operation
- XOR and the one-time pad: https://www.khanacademy.org/computing/computer-science/cryptography/ciphers/a/xor-and-the-one-time-pad

### Walkthrough

1. Participants are introduced to the second part of the stream cipher challenge, where they need to recover the encryption's secret key.
2. The first hint reminds participants about the properties and operation of the XOR cipher, which were crucial in Part 1. It suggests that the same principles may help in recovering the key in this challenge as well.
3. Participants are encouraged to leverage the knowledge gained from Part 1. Try to focus on the key stream, consider its length, and explore brute-force techniques to recover the secret key.

### Flag

`BEGINNER{XORCipherSuccess}`

</details>

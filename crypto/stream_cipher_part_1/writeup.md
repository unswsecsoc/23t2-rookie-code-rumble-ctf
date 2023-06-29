# Stream Cipher (PART 1)

## Authors

- @Baking2Trees

## Category

- Crypto

## Description

You are Elon Musk, the visionary entrepreneur and CEO of SpaceX. You just enrolled in a new security course where everyone has formed groups, except for you. One of the participants challenges you to decrypt a ciphertext using a stream cipher algorithm. They want to test your cryptography skills before partnering up with you. Can you decrypt the message and prove your expertise in cryptography?

## Difficulty

- Easy

## Hints

1. Think of a fundamental operation that is widely used in many encryption schemes.
2. The properties and operation of the XOR cipher can help you recover the key.
3. Pay attention to the relationship between the key stream and the ciphertext to recover the plain text.
4. 'Space is included in the flag.'

## Files

- cipherText.txt
- keyStream.txt

Try include a link to the file where possible (such as within a repo).

## Solution

<details>
<summary>Spoiler</summary>

### Idea

The challenge revolves around XOR encryption using a stream cipher. Participants need to understand the principles of XOR and its role in encryption to recover the key.

An XOR encryption is used mainly in encrypting data online because of its simplicity and efficiency in generating the keystream. There are also other stream cipher algorithms such as Vernam cipher, RC4, or A5/1.

Visit these sites to learn more about stream ciphers:

- "Handbook of Applied Cryptography" by Alfred J. Menezes, Paul C. van Oorschot, and Scott A. Vanstone, Chapter 6: http://cacr.uwaterloo.ca/hac/
- Securing Stream Ciphers (HMAC) - Computerphile: https://youtu.be/wlSG3pEiQdc
- XOR bitwise operation: https://www.khanacademy.org/computing/computer-science/cryptography/ciphers/a/xor-bitwise-operation
- XOR and the one-time pad: https://www.khanacademy.org/computing/computer-science/cryptography/ciphers/a/xor-and-the-one-time-pad

### Walkthrough

1. Participants should read the challenge description carefully. They are required to decrypt a ciphertext using a stream cipher algorithm as part of a challenge presented to Elon Musk.
2. The first hint suggests understanding the fundamental operation used in many encryption schemes. In this case, the operation is XOR (exclusive OR).
3. Participants are encouraged to experiment with XOR bitwise operations, understand how XOR combines bits, and explore how it can be used to recover the key and decrypt the ciphertext.
4. The recovered plain text will give participants the clue to obtain the correct flag, in the format of 'BEGINNER{}'.

### Flag

`BEGINNER{Elon Reeve Musk}`

</details>

#!/usr/bin/python3
from pwn import *

conn = remote("localhost", 1337)


def check(subs):
    conn.recvuntil(b"> ")
    conn.sendline(subs.encode())
    dat = conn.recvline().decode()
    if "That's the flag" in dat:
        print(subs, "is the flag!")
        exit()
    return "Yes" in dat


# You could have more characters here if you didn't know what characters
# were in the flag. It would work the same
allowed_chars = "abcdefghijklmnopqrstuvwxyz"

figured_out_word = ""
done_to_end = False

while not done_to_end:
    found_one = False
    for letter in allowed_chars:
        if check(figured_out_word + letter):
            figured_out_word = figured_out_word + letter
            print(figured_out_word)
            found_one = True
            break
    if not found_one:
        done_to_end = True


done_to_start = False

while not done_to_start:
    found_one = False
    for letter in allowed_chars:
        if check(letter + figured_out_word):
            figured_out_word = letter + figured_out_word
            print(figured_out_word)
            found_one = True
            break
    if not found_one:
        done_to_start = True

print("Done! Here is the flag:", figured_out_word)

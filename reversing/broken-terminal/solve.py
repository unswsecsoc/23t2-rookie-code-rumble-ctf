from pwn import *

target = remote("pwn.ctf.secso.cc", 6000)
#target = remote("127.0.0.1", 9999)


data = target.recvall().decode('ascii')
print(data)

vec = [11, 59, 4, 21, 37, 44, 53, 8, 34, 14, 1, 56, 62, 66, 0, 31, 26, 25, 24, 30, 23, 29, 1, 28, 33, 40, 48, 64, 72, 17, 41, 49, 65, 70, 51, 42, 50, 19, 43, 52, 20, 69, 18, 47, 63, 71, 27, 38, 16, 46, 45, 60, 61, 67, 68, 39, 55, 7, 3, 13, 36, 10, 58, 35, 4, 12, 32, 9, 54, 57, 2, 15, 22]
proper_flag = ["B", "E", "G", "I", "N", "N", "E", "R"] + ["A"]*(73-8)

for i, ch in enumerate(data):
	proper_flag[vec[i]] = ch

print(''.join(proper_flag))




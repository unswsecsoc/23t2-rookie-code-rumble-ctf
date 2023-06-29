# Broken Terminal

## Authors

- @ItsIronicIInsist


## Category
- Reverse Engineering

## Description

We've come across a buggy terminal - we think it might holds some key secrets regarding the aliens.
Are you able to recover the message?

## Difficulty

- Hard

## Points

100

## Hints


## Files
- [broken_terminal](./_ctfd/files/broken_terminal): Compiled binary
- [broken_terminal.c](./_ctfd/files/broken_terminal.c): Source code
- [solve.py](./solve.py): Solve script



## Solution

<details>
<summary>Spoiler</summary>

### Idea

Use your knolwedge of the flag format to decrypt the encrypted code, and then realize the output is the scrambled flag.
Use a dummy flag to figure out how to descramble the flag, and apply to the real output.

### Walkthrough

1. **Time isnt real**
	- The source code here is very short
	- We do some unimportant stuff (set alarm, disable buffering)
	- Then we read the flag onto the stack, and generate a random seed, before calling setup_worker
	- First thing to realise - reading the flag onto the stack overwrites the seed value, because `Data` is a union.
	- We will also need to create a dummy flag to avoid a SIGSEGV here
2. **what is what doing**
	- `setup_worker` maps a page into memory, thats readable, writeable, and executable.
	- Then, it XOR's what's content onto that page, using the seed value.
	- Then, it treats the page like a function, and calls it.
	- Because the flag overwrote the random-value, seed will be the first 8 bytes of the flag - `BEGINNER`
	- So, set our flag to be `BEGINNER{random_value}` (so that is decrypts properly)
3. **Decrypted**
	- In something like gdb, we then break before we call `base`.
	- The XOR-ing turned `what` into valid x86-64 assembly.
	- Reading through this will take some time but essentially:
	- It reads the flag into memory
	- Loops 73 times, and forks for each
	- Each forked process waits for a given amount of time, and then outputs a byte of the flag
4. **A shortcut**
	- The time each process waits is dependant on the un-encrypted `what`, and one could map that out.
	- Instead, a faster way is to set the flag to something like `BEGINNER{abcdefghijklmnopqrstuvwxyzACDFHJKLMOPQSTUVWXYZ0123456789!@#$%^&}`
	- This flag doesnt repeat values, except for the BEGINNER
	- We can then observe the output of broken_terminal, and track where each character ends up
	- e.g if the first char is 'c', it should be in the 11th position
5. **Descrambling the actual output**
	- Then, we take this translation, and apply it to the actual output.
	- You should then get the proper flag, descrambled
	- There is a slight race-con, where an 'n' and '.' may be swapped, but it should be pretty visible and easy to fix

### Flag

`BEGINNER{We_are_contacting_you_about_your_extended_spaceship_warranty...}`

</details>



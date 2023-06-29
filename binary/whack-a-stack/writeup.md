# whack-a-stack

## Authors

- @larrabyte

## Category

- Binary

## Description

We've received reports that bank accounts across the globe have been drained by myterious actors.
Further investigation reveals the destination for these transactions to be an alien server.
We need you to check it out.

Connection info: `nc pwn.ctf.secso.cc 5003`

## Difficulty

- Medium

## Points

100

## Files

- [a.out](./_ctfd/files/a.out): Statically compiled binary.
- [challenge.c](./_ctfd/files/challenge.c): Source file.
- [solve.md](./solve.md): The intended solution.

## Solution

<details>
<summary>Spoiler</summary>

### Idea

To overflow the credit card digit array and overwrite the return address of `extract_le_monies` with `here_is_the_flag`.

### Walkthrough

1. **Getting a cursory overview.**
    - Simply reading and running the challenge source is always a good first step to finding a solution.
    - We're asked to provide some credit card numbers. Turns out they can't be random and have to pass some sort of algorithm.
    - Reading the source code, we see a bunch of extra functions for signal handling? Seems to print out extra information if the program encounters a segmentation fault.
    - The flag function is present, but is never called anywhere. So somehow, we seemingly have to redirect program execution solely via the credit card input.
2. **An idea!**
    - The digits are read in via `read_from_stdin`, which takes as input a `char*` and uses it as a buffer to write data into. It only terminates reading when it encounters an `EOF` or `\n`. What happens if we simply write more data then the program expects?
    - It still seems to work for inputs under 32 characters... ah, but that's because the `card` type
    has a 32-character array, seemingly to prevent nefarious people like us from exploiting the program. OK, let's try more. Say, 100 random characters.
    - Now the program crashes, and calls that funky signal handler from earlier. We see the address of
    `here_is_the_flag`!
3. **Experimenting with input.**
    - What if I try putting a bunch of As instead of random characters?
    - The signal handler output says that `rbp` is equal to `0x4141414141414141`. How interesting.
    - `0x41` is ASCII A... so we now know we can control certain CPU registers. But which ones do we need to control in order to change where the program executes?
    - Some searching indicates the binary is built for `x86_64`, and that `rip` is our target.
4. **Controlling the instruction pointer.**
    - How can we control the instruction pointer via a simple buffer overflow?
    - Well, if we're in a function, and we have to return at some point, the CPU must store that return address somewhere. Let's do some searching on how `x86_64` implements this.
    - It's done on the stack! Specifically, the `call` instruction pushes the address to return to before jumping to called address. The `ret` instruction pops this address back into `rip`.
    - We know the credit card array is 32 characters in size, so why don't we try an input of 32 characters and then the address of `here_is_the_flag`?
    - Doesn't seem to work. Why? Some disassembly may be required.
    - Turns out this binary also pushes `rbp` at the beginning of a function to save the stack frame address of the previous function, which is standard on programs built without optimisation. If we adjust our input to be (32+8) characters and then the address, we get the flag.

### Flag

`BEGINNER{nOOO_n07_my_v_buck5!11!11!!!}`

</details>

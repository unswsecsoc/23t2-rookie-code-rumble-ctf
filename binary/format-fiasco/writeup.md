# format-fiasco

## Authors

- @larrabyte

## Category

- Binary

## Description

We've seen a notable increase in activity around the Martian north pole.
With some extremely powerful binoculars, it seems like they've managed
to construct a supercomputer to help with their war effort!
We need you to break in and extract any secret documents you can find.

Connection info: `nc pwn.ctf.secso.cc 5000`

## Difficulty

- Medium

## Points

100

## Files

- [a.out](./_ctfd/files/a.out): Statically compiled binary.
- [challenge.c](./_ctfd/files/challenge.c): Source file.
- [solve.py](./solve.py): The intended solution.

## Solution

<details>
<summary>Spoiler</summary>

### Idea

To use format strings to write a non-zero value into the `administrator` variable.

### Walkthrough

1. **Getting a cursory overview.**
    - Simply reading and running the challenge source is always a good first step to finding a solution.
    - We get a login prompt, and then get dropped into some sort of shell.
    - The only things we seem to be able to do are tied to our username (eg. print it out, update it and get a quote associated with it).
    - Reading the source code, we see the flag is printed whenever we ask for a quote if the `administrator` variable is non-zero. But it's never written to...
2. **Static analysis.**
    - Our goal is to somehow write to the `administrator` variable.
    - We can get its address easily via the `debug` command.
    - Since everything seems to be oriented around usernames, let's focus our attention there.
    - Buffer overflows don't seem to be the right way to go since `read` uses `fgets` with a correct size.
    - `printf(username)` differs from `printf("%hhu\n", administrator)` in the `whoami` command. Why wasn't it written like `printf("%s\n", username)`?
    - If we try to compile it locally on our machine, we get a format string warning?
    - Let's do some searching.
3. **An arbitrary read/write primitive?**
    - So it turns out that we can read and write to arbitrary memory via format strings!
    - And we control the format string in the form of the username!
    - Reading memory can be done by placing some sort of integer specifier  (`%d`, `%p`, etc).
    - Writing memory can be done by using `%n` (which writes the number of characters printed up to that point to an address provided to `printf`, details omitted for brevity).
4. **Conjuring up a solution.**
    - Theoretically, we can now read and write anywhere in program memory.
    - Our target: the `administrator` variable. We already have its address via the `debug` command.
    - By placing a bunch of `A`s and then `%p`s in our username, we can see using the `whoami` command that the username itself is stored on the stack (since we see 0x41414141..., which is ASCII A in hexadecimal).
    - All we have to do now is get the address of `administrator`, place it in our username somewhere and then use format specifiers to move the stack pointer to point to the address, and then use `%n` to write to it.
    - More details can be found in [solve.py](./solve.py).
    - Once that's done, running the `quote` command prints the flag.

### Flag

`BEGINNER{1_w0nd3r_1f_7h3y'v3_533n_7h3_cur10517y_r0v3r}`

</details>

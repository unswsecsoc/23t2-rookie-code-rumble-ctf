# Exceptional

## Authors

- @larrabyte

## Category

- Misc

## Description

To prepare you for the upcoming alien war, we need you to master the art of flag capturing in multiple languages - this one is of a particularly slithery variety. The goal is simple: get in, get flag, get out. Good luck.

Connection info: `nc pwn.ctf.secso.cc 1000`

## Difficulty

- Medium

## Points

100

## Files

- [challenge.py](./src/challenge.py): Source file.
- [solve.md](./solve.md): The intended solution.

## Solution

<details>
<summary>Spoiler</summary>

### Idea

To raise an exception that doesn't derive from `OSError`.

### Walkthrough

1. **Getting a cursory overview.**
    - Simply reading and running the challenge source is always a good first step to finding a solution.
    - The program seems to take a filesystem path as input and compares the read file data to a flag variable.
2. **So... initial ideas?**
    - An idea that may come to mind is to brute force paths until we find the flag.
    - However, we are working with a completely unknown box (except for the fact that it runs Python).
    - To make matters worse, the flag file may not even exist.
3. **Perhaps some further insight may be required.**
    - The name of a challenge is more often than not a clue for finding the intended solution.
    - This challenge is named `exceptional`, and the source does in fact take advantage of exception handling.
    - Perhaps we should focus our attention there?
4. **A theoretical analysis.**
    - What would happen if `open` threw an exception? In our case, we catch all exceptions derived from
    `OSError`, print out an error message and then exit.
    - What if `open` threw an exception that didn't derive from `OSError`? The call to `matches` is also wrapped in a try-catch block, which then prints the flag based on the value of `matches`.
    - But the function and the variable have the same name?
    - If the function exits early via an exception, then the `if` statement will be using the function itself as a boolean, which always evaluates to `True` in Python.
5. **Drafting up a solution.**
    - Our goal now is to get `matches` to throw an exception that doesn't derive from `OSError`.
    - The documentation seems to indicate that `OSError`-derived exceptions are raised when a file can't be opened.
    - From this point, there are two paths one can take.
6. **Just a little bit of fuzzing.**
    - The type hinting and assertions allow for `bytes` to be passed as well as `str` objects.
    - Perhaps this could be the path to a solution? Let's test on a local Python interpreter.
    - The simplest instance of a `bytes` object is the empty byte string. Running `open(b"")` raises `FileNotFoundError`, which derives from `OSError`.
    - OK, how about a null byte? Running `open("b\x00")` raises `ValueError`!
    - And there we have the intended solution.
7. **An alternative route.**
    - Note that the documentation says that `OSError`-derived exceptions are raised when a file can't be opened.
    - What about while reading? By default, `open` will attempt to read and decode file data as text (specifically, it expects UTF-8 strings).
    - Passing it the path of a non-UTF-8 file (say, a binary) will cause `file.read()` to raise `UnicodeDecodeError`!
    - With some simple testing, we can pass `/bin/ls` (or any other binary filepath) and similarly get the flag.
    - This *technically* requires knowledge of the filesystem layout of the server, which was not given, however many people made the reasonable assumption that the box ran on Linux and simply passed in the path to a standard binary.

### Flag

`BEGINNER{4nd_i_7h0ugh7_j4v45cr1p7_w4s_w31rd}`

</details>

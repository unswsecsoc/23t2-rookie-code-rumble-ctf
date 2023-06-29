# heap-house-party

## Authors

- @larrabyte

## Category

- Binary

## Description

Expert 1337 hackers have managed to stumble across a top secret alien mainframe.
We hear that there may be data on board which will help with the war effort.
Do you think you can help?

Connection info: `nc pwn.ctf.secso.cc 5001`

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

To make `numbers` point to the same allocation as `stats`.

### Walkthrough

1. **Getting a cursory overview.**
    - Simply reading and running the challenge source is always a good first step to finding a solution.
    - We get asked a series of questions, input some numbers and then get an average spat back out at us.
    - Reading the source code, we see that we have to get the sum of all the `stats` members to be equal to `-1`.
    - The code never writes to `stats` after `memset`, which zeroes out all the fields.
    - It does call `free(stats)` if allocating `numbers` fails.
2. **Some hypothesising.**
    - Let's say we were able to get ourselves into a situation where `free(stats)` was called.
    - From the code, we see that this means the first allocation for `numbers` must have failed, and it is attempting to get some spare memory by freeing `stats`.
    - What if we could make the second attempt at allocating `numbers` return the allocation for `stats`?
    - The size of the `stats` structure looks to be comprised of 4 integers, making it 16 bytes.
        - This *technically* isn't true in general, but a reasonable assumption can be made here.
        - This can be double-checked with the provided binary through some disassembly.
    - The plan now is to fail the first allocation, and then provide a size of `16` for the second allocation.
3. **Crafting the input.**
    - Some searching reveals that providing too large of a size to `malloc` will cause it to return `NULL`. The easiest way to do this is to provide `-1` for `count` (since `malloc` takes a `size_t` as input, negative inputs will be implicitly cast to extremely large positive integers).
    - Then, we provide `4` for `count` in order to execute `malloc(16)`.
    - As the source code suggests, we set the sum of this new array equal to `-1`, and we get the flag.

### Flag

`BEGINNER{al13n_m3m0ry_4ll0c470r5_k1nd4_w4cky}`

</details>

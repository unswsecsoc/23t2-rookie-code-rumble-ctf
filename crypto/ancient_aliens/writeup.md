# ancient_aliens

## Authors

- @CaptainBoggle


## Category
- crypto

## Description

WARNING!!! THIS CHALLENGE IS HARD (i think)!!!

We have been intercepting the alien communications, and it seems they are using an old, cryptographically insecure hashing function with constraints as a means of encrypting their messages...
Using the intercepted data, we have created a small testing program. Using the source code for this program, determine which input string will pass the checks in place. 

## Difficulty

- Hard



## Files
- [ancient_aliens.c](./_ctfd/files/ancient_aliens.c): TODO add description



## Solution

<details>
<summary>Spoiler</summary>

### Idea

Reverse the constrained CRC64 algorithm using symbolic execution.

### Walkthrough

# Method 1: KLEE
See solve.c for writeup.

# Method 2: MATHS???

Something about chinese remainder theorem, writeup by @yellowsubmarine1447 coming soon TM.

### Flag

`BEGINNER{iM_noT_reDUnDanT}`

</details>

# Title

## Authors

- @GeorgeMuscat

## Category

- Recon

## Description

You can access this challenge via ssh. Command: `ssh officer@pwn.ctf.secso.cc -p  2200` and password `iCANTstandROOKIES1337`.

Through advanced reconnaissance, we have discovered the ssh credentials to an officer's machine. Exploit these credentials to gain access to the machine and collect critical operations intelligence.

## Difficulty

- Easy

## Points

000

### Solution

<details>
<summary>Spoiler</summary>

### Idea

This challenge is designed to be an introduction to linx recon. Often important information will be stored in plain sight as uses with bad OpSec will not consider a breach of their systems likely.

Users will create shortcuts to prevent tedious repetition. If done incorrectly, users may expose sensitive information.

### Walkthrough

1. Gain access to the box via the command in the description
2. Perform standard recon by running `alias` to see a list of the user's aliases
3. See the alias `woop`, looks a little sus.
4. Run `woop`
5. Profit

### Flag

`BEGINNER{sUpEr_FasT_aNd_EaSy_AliAses_w00p!}`

</details>

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

Internal organisational information may seem

### Walkthrough

1. Gain access to the box via the command in the description
2. See the MOTD appear for half a second and then get cleared
3. Check `.bashrc`
4. See sensitive information (the flag)
5. Profit

### Flag

`BEGINNER{SeCReT_OfFiCeR_MoTD_2359fabe}`

</details>

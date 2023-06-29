# hostage

## Authors

- @CaptainBoggle


## Category
- forensics

## Description

I was writing a really cool CTF challenge, but when the aliens attacked, they installed some sort of virus on my computer, and all my files got encrypted, including the challenge!
Here is the encrypted flag file, I guess you can have the points for the challenge if you manage to get it unlocked for me...
Oh, and they also left this ransom note, I guess it might come in handy?

## Difficulty

- Medium

## Files
- [flag.png.key](./_ctfd/files/flag.png.key): TODO add description
- [h0w_t0_rec0very_files.txt](./_ctfd/files/h0w_t0_rec0very_files.txt): TODO add description


## Solution

<details>
<summary>Spoiler</summary>

### Idea

Find open source software to decrypt files encrypted by popular ransomware, using the ransom note as a way to identify the original encryptor.

### Walkthrough

A google search for "h0w_t0_rec0very_files", or many strings inside the ransom file such as the email address, or just random sentences, turns up
many results mentioning PwndLocker. Hop on GitHub and search for PwndLocker, then run the script found in the repo:
https://github.com/hasiblatif/PwndLocker-ransomware-decryptor 
to decrypt the file containing an image of the flag text.

### Flag

`BEGINNER{i_hoP3_y0u_d1dnT_p4y_F0r_th1S}`

</details>

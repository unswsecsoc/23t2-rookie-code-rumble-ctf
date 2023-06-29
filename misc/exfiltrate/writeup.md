# Exfiltrate

## Authors

- @ssparrow

## Category

- misc

## Description

The aliens propose a guessing game. Surely your computer science skills are more valuable than luck?

Connection info: `nc pwn.ctf.secso.cc 1337`

## Solution

<details>
<summary>Spoiler</summary>

### Idea

The challenge will tell us if the flag contains a provided substring. The goal is to retrieve the whole flag.

### Walkthrough

1. We need to create an algorithm to extract the flag. Let's say we pick a letter X such that when we give X
   to the program, it says that it is inside the flag.
2. Let us try entering XY into the program where Y is another character. If it is not inside the flag,
   try a different character as Y. Repeat until it is.
3. Now try entering XYZ where Z is another character.
4. You can probably see where this is going. However, eventually we will end up with a string where
   there is no character after it. This probably means that it is the end of the flag.
5. What we can do now is start adding letters to the front, until we get to the start of the flag.
6. I wrote a script to do this, see [solve.py](./solve.py)

Side note: This kind of methodology is often used in real world hacking. Search up "boolean SQL injection"
for more info.

### Flag

`BEGINNER{thisstringisimpossibletoguessyouwillneverguessitmanually}`

</details>

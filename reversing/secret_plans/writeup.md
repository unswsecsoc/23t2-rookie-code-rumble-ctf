# Secret Plans

## Authors

- @ItsIronicIInsist


## Category
- Reverse Engineering

## Description

The aliens have been broadcasting about how extremely secret their super secret plans are. Are you able to track them down?

## Difficulty

- Easy

## Points

50

## Hints


## Files
- [secret_plans](./_ctfd/files/secret_plans): Challenge binary



## Solution

<details>
<summary>Spoiler</summary>

### Idea

Flag is stored in .rodata of binary, but wont by detected by strings + grep

### Walkthrough

1.**Running the binary**
  - Which does practically nothing
  - Opening gdb, we can inspect the main function (by breaking on puts if we need to)
  - But it doesnt hold much
2.**Where's data stored?**
  - Given theres no hidden functionality, and no interactivity, the flag's probably just stored somewhere on the binary.
  - There's a couple areas in the elf that store 'variables', mainly the .bss and .rodata sections
  - `objdump -s secret_plans` will dump all sections - sure enough, in .rodata the flag is there
  - Its spliced with newlines, which would've prevented it from showing up in commands like `strings`


### Flag

`BEGINNER{h0w_d1d_y0u_f1nd_the_s3cret_str1ng??}`

</details>

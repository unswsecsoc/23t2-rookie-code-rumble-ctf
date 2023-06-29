# Starships

## Authors

- @ItsIronicIInsist


## Category
- Binary Exploitation

## Description

In the academy, we have the state of the art combat simulators to prepare you for any skirmishes out there!
We're going to have you run through a few simulations to ensure you've got what it takes!

## Difficulty

- Medium

## Points

50

## Hints


## Files
- [starships](./_ctfd/files/starships): Compiled binary
- [starships.c](./_ctfd/files/starships.c): Source
- [solve.py](./solve.py): Solve script


## Solution

<details>
<summary>Spoiler</summary>

### Idea

Enter in bogus values so that unitialized memory is leaked, why contains the time used for seeding the rand func.
Just enter that into srand in your own program and re-generate all the coords to fire at.

### Walkthrough

1. **Reading the code explains the code**
	- We are essentially playing battleships
	- When inspecting a binary challenge, always look for where you can interact / enter data / affect state.
	- The only place is when we are entering in coords to fire at (so bug must be related).
2. **Entering weird values**
	- What are weird values we can enter?
	- Negative values, or very big ones are good ideas, but the `valid_coords` function shuts down those ideas
	- What happens if we enter values that aren't numbers?
3. **Leaking memory**
	- If we enter something like `a b` we'll see some values still get printed for `x` and `y`, but they're weird
	- Essentially, because scanf didn't write to `x` and `y`, and because we dont initialize them, we are reading unitialized memory.
	- They'll be set to whatever the stack space they occupy was set to earlier. For `x`, this is the time value used for seeding random.
4. **Not so random**
	- We can take the time value then, and use it to seed random for us as well, and regenerate where all the ships will be located (see `solve.py`)
	- Then, we just guess those coords, and get the flag


### Flag

`BEGINNER{y0u'r3_a_n4tur4l_k1d!}`

</details>

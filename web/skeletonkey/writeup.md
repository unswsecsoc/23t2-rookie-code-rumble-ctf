# Skeleton Key

## Authors

- @ssparrow

## Category

- web

## Description

The door is locked, but can you find the skeleton key?

Find it here: `https://skeletonkey.ctf.secso.cc`

## Solution

<details>
<summary>Spoiler</summary>

### Idea

There is a Javascript algorithm that can be broken by giving it unexpected input.

### Walkthrough

1. In essence, the code uses `createNumberedPairs` to turn something like this:

```
[4,7,8]
```

into this:

```
[[0,4], [1,7], [2,8]]
```

`numberedPairsToArray` does this action in reverse.

To get the flag, we need to make the JSON encoding of the input not equal to the JSON encoding of the output.

Without further ado, you can use the payload `{}` to get the flag. Let's see how this works.

`{}` is the JSON notation for an empty object. While running `Object.keys` on an array,
we get a list of the indexes of the array. However, on an object, we get the keys of the
object, which in this case is nothing. This will therefore return an empty list `[]`.

`numberedPairsToArray` will take the empty list and turn it into the inverse, but as it
is an empty input, it returns an empty output.

Therefore, our input was `{}` and our output was `[]`.

It's completely fine to just stumble along a solution like this. The main takeaway from this
challenge is that when hacking, sometimes it helps to think about all the different types of
data you can input.

### Flag

`BEGINNER{java5cr1pt_15_an_0dd_langu4g3}`

</details>

# Astral

## Authors

- @larrabyte

## Category

- Web

## Description

We suspect that alien war plans are being distributed via a newly uncovered
intergalactic file sharing service. We need you to go in and investigate.

Find it here: `https://astral.ctf.secso.cc`

## Difficulty

- Medium

## Points

100

## Files

- [main.rs](./src/src/main.rs): The server source code.
- [solve.md](./solve.md): The intended solution.

## Solution

<details>
<summary>Spoiler</summary>

### Idea

To exploit local file inclusion to find a hidden flag file on the server.

### Walkthrough

1. **Getting a cursory overview.**
	- Navigating to the website, we see a plain page with some text and an upload form.
	- OK, not much here to manipulate. Let's upload a small file.
	- We get back a string of the form `/read/<some long random string>`. Presumably, we navigate to it.
	- Our file gets served back to us (Chomium-based browsers may download a compressed artefact, but that is client-side, Astral itself provides the raw data).
2. **Basic checks.**
	- What if we upload nothing? What if we upload something really big?
	- We get an error saying that our file must be between 1 and 10,240 (10K) bytes.
	- OK... so filesize manipulation might not be it.
	- Our other avenue is the long string it gives back to us upon successful file upload.
3. **Is there anything funky about this string?**
	- That long random part seems a little suspicious. What if we changed it slightly? Let's delete one character off the end.
	- The server returns `No such file or directory (os error 2)`!
	- This means that the long string is actually a filename? How interesting.
4. **Navigating the filesystem.**
	- So what if we instead try to go to `/read/..`?
	- If you tried this on your browser this most likely wouldn't work, but only because of browser URL shenanigans. If we switch to a raw HTTP client and try again, we get a 418 response.
	- This is definitely not normal (the server is almost certainly not a teapot), and indicates we're on the right track.
	- Since we gave it `..`, we now know the contents of the parent directory. What if we keep going? What about `/read/../..`?
	- This unfortunately won't work because `/` is a special character - we need to URL-encode it.
	- Trying `/read/..%2F..` works, and it seems to have given us back the root filesystem!
5. **The flag.**
	- Do we see anything out of the ordinary?
	- Ah, a `ctf` entry. Let's navigate there with `/read/..%2F..%2Fctf`.
	- Ah, a `secret` entry. Let's navigate there with `/read/..%2F..%2Fctf%2Fsecret`.
	- Repeat until you find `flag.txt`.

### Flag

`BEGINNER{3v3n_al1en5_c4n_appr3c14t3_blaz1n6_f4st_4nd_m3m0ry_s4f3_c0d3}`

</details>

/*
This solution follows the instructions given on the first KLEE tutorial http://klee.github.io/tutorials/testing-function/
with the addition of klee_assert(0) to make it easier to locate the desired test case

First we compile to LLVM bytecode with no optimisations:
> clang -I /opt/homebrew/Cellar/klee/2.3_4/include -emit-llvm -c -O0 -Xclang -disable-O0-optnone ancient_aliens_solved.c

Then we run with KLEE, which takes 5 seconds on my laptop:
> klee --optimize ancient_aliens_solved.bc

        KLEE: WARNING: Module and host target triples do not match: 'arm64-apple-macosx12.0.0' != 'arm64-apple-darwin21.6.0'
        This may cause unexpected crashes or assertion violations.
        KLEE: output directory is "/Users/boggle/Documents/klee-out-23"
        KLEE: Using STP solver backend
        warning: linking module flags 'SDK Version': IDs have conflicting values ('[2 x i32] [i32 12, i32 3]' from klee_overshift_check64_Release.bc with '[2 x i32] [i32 13, i32 1]' from ancient_aliens_solved.bc)
        KLEE: ERROR: (location information missing) ASSERTION FAIL: 0
        KLEE: NOTE: now ignoring this error at this location

        KLEE: done: total instructions = 5909
        KLEE: done: completed paths = 29
        KLEE: done: partially completed paths = 1
        KLEE: done: generated tests = 30

We can see that the assertion was triggered, so our desired path was found.
We check to see which case triggered the assertion:
> ls klee-last/

        assembly.ll            test000001.ktest       test000006.ktest       test000011.ktest       test000016.ktest       test000021.ktest       test000026.ktest       test000030.kquery
        info                   test000002.ktest       test000007.ktest       test000012.ktest       test000017.ktest       test000022.ktest       test000027.ktest       test000030.ktest
        messages.txt           test000003.ktest       test000008.ktest       test000013.ktest       test000018.ktest       test000023.ktest       test000028.ktest       warnings.txt
        run.istats             test000004.ktest       test000009.ktest       test000014.ktest       test000019.ktest       test000024.ktest       test000029.ktest
        run.stats              test000005.ktest       test000010.ktest       test000015.ktest       test000020.ktest       test000025.ktest       test000030.assert.err

We can see test000030.assert.err is the test case with .err appended, so we know that is the one that hit our target.
We check to see the value of str in that case:
> ktest-tool klee-last/test000030.ktest

        ktest file : 'klee-last/test000030.ktest'
        args       : ['ancient_aliens_solved.bc']
        num objects: 1
        object 0: name: 'str'
        object 0: size: 26
        object 0: data: b'BEGINNER{iM_noT_reDUnDanT}'
        object 0: hex : 0x424547494e4e45527b694d5f6e6f545f726544556e44616e547d
        object 0: text: BEGINNER{iM_noT_reDUnDanT}

And there we have the flag!

*/

#include <stdbool.h>
#include <stdint.h>
// #include <stdio.h> no IO for KLEE
#include <string.h>

// Includes for KLEE
#include <assert.h>
#include <klee/klee.h>

#define SIZE 26

uint_fast64_t crc64(uint_fast64_t poly, const void *data, size_t data_len) {
	const unsigned char *d = (const unsigned char *)data;
	unsigned int i;
	bool bit;
	unsigned char c;
	uint_fast64_t crc = 0;

	while (data_len--) {
		c = *d++;
		for (i = 0; i < 8; i++) {
			bit = crc & 0x8000000000000000;
			crc = (crc << 1) | ((c >> (7 - i)) & 0x01);
			if (bit) {
				crc ^= poly;
			}
		}
		crc &= 0xffffffffffffffff;
	}
	return crc & 0xffffffffffffffff;
}

bool check_string(uint8_t str[SIZE]) {
	int i = 0;
	for (i = 0; i < SIZE; i++) {
		if ((str[i] < 'A' || str[i] > '~')) {
			return false;
		}
	}
	if ((crc64(0x42f0e1eba9ea3693, &str[0], SIZE) != 0x8d264fc84bbeede9) ||
	    (crc64(0xad93d23594c935a9, &str[0], SIZE) != 0x714ceac2d7a3aaa8) ||
	    (crc64(0x1337C0DE15BAAAAD, &str[0], SIZE) != 0x780486b31ee4df55)) {
		return false;
	}
	return true;
};

int main() {
	uint8_t str[SIZE];

//  fread(str, sizeof(char), SIZE, stdin); 
    klee_make_symbolic(str, sizeof str, "str"); // create a symbolic string, dont read from stdin
	
    if (check_string(str)) { 
        // remove print
		// printf("That's right! You got the flag!!!!");
        klee_assert(0); // tell klee to append .err to cases that land here
	}
    //else {
        // remove print
		// printf("NOPE"); 
	//}

	return 0;
}

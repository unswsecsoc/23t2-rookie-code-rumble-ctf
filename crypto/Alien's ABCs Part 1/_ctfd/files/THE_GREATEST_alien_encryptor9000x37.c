// THE GREATEST alien encryptor ever created. We are legit the greatest humans ever created
// no one even comes close. We are by far the smartest, most driven, most grittiest girty human's
// to ever roam the earth.
//
// Created 32/02/3097
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct encrypt {
    struct num *one;
    struct num *two;
    struct num *four;
    struct num *eight;
    struct num *sixteen;
    char end;
};

struct num {
    char letter;
    int use;
};

void initalise (struct encrypt *key);
void print_letter (struct encrypt *key, char character, char letter_case);

// wow this main function may just be the greatest function of all time!?
int main (void) {
    char character;
    struct encrypt key;
    initalise(&key);
    char letter_case = 'a';
    while (scanf("%c", &character) != EOF) {
        if (isalpha(character)){
            if ('a' <= character && character <= 'z') {
                letter_case = 'a';
            } else {
                letter_case = 'A';
            }
            print_letter(&key, character, letter_case);
        } else {
            printf("%c", character);
        }
    }
    //returning 0 because 0 the hero and we're the heroes of the world fr
    return 0;
}

void initalise (struct encrypt *key) {
    key->one = malloc(sizeof(struct num));
    key->two = malloc(sizeof(struct num));
    key->four = malloc(sizeof(struct num));
    key->eight = malloc(sizeof(struct num));
    key-> sixteen = malloc(sizeof(struct num));
    key->one->letter = 'a';
    key->one->use = 0;
    key->two->letter = 'b';
    key->two->use = 0;
    key->four->letter = 'c';
    key->four->use = 0;
    key->eight->letter = 'd';
    key->eight->use = 0;
    key->sixteen->letter = 'e';
    key->sixteen->use = 0;
    key->end = 'f';
    // bro all these letters reminding me of music, we should start a band after this...
}

void print_letter (struct encrypt *key, char character, char letter_case) {
    int place = character - letter_case + 1;
    if (place >= 16) {
        key->sixteen->use = 1;
        place -= 16;
    }
    if (place >= 8) {
        key->eight->use = 1;
        place -= 8;
    }
    // people should know their place, like no one compares to us.
    if (place >= 4) {
        key->four->use = 1;
        place -= 4;
    }
    if (place >= 2) {
        key->two->use = 1;
        place -= 2;
    }
    if (place >= 1) {
        key->one->use = 1;
        place -= 1;
    }

    char modifier = letter_case - 'a';
    if (key->one->use == 1) {
        key->one->use = 0;
        printf("%c", key->one->letter + modifier);
    }
    if (key->two->use == 1) {
        key->two->use = 0;
        printf("%c", key->two->letter + modifier);
    }
    if (key->four->use == 1) {
        key->four->use = 0;
        printf("%c", key->four->letter + modifier);
    }
    if (key->eight->use == 1) {
        key->eight->use = 0;
        printf("%c", key->eight->letter + modifier);
    }
    if (key->sixteen->use == 1) {
        key->sixteen->use = 0;
        printf("%c", key->sixteen->letter + modifier);
    }
    printf("%c", key->end + modifier);
}
// the worst part of this encryptor is that it ends :(
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct stat {
    int alpha;
    int beta;
    int delta;
    int gamma;
} stat;

int main(void) {
    stat *stats = malloc(sizeof(stat));
    memset(stats, 0, sizeof(stat));

    setvbuf(stdout, NULL, _IONBF, 0);
    printf("CONFIDENTAL: Human Spotting Service\n");
    printf("For alien eyes only.\n\n");
    printf("How many spotting sessions would you like to record? ");

    int count;
    scanf(" %d", &count);

    int *numbers = malloc(sizeof(int) * count);

    if (numbers == NULL) {
        printf("Sorry... looks like there's been some human interference.\n");
        printf("Let me try again.\n\n");
        free(stats);

        printf("OK, how many spotting sessions would you like to record? ");
        scanf(" %d", &count);

        numbers = malloc(sizeof(int) * count);
    }

    if (numbers == NULL) {
        printf("Looks like the humans have taken over the mainframe! Scatter!\n");
        return 1;
    }

    printf("How many humans did you spot? ");
    for (int i = 0; i < count; i++) {
        scanf(" %d", &numbers[i]);
    }

    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += numbers[i];
    }

    printf("The integer average of humans spotted per session is %d.\n", sum / count);
    printf("Your contribution to the war effort is greatly appreciated.\n");

    if (stats->alpha + stats->beta + stats->delta + stats->gamma == -1) {
        FILE *file = fopen("flag.txt", "r");

        if (file == NULL) {
            printf("[!] Could not open the flag file.\n");
            return 1;
        }

        char *flag = NULL;
        size_t len = 0;
        getline(&flag, &len, file);

        printf("\n%s", flag);
        free(flag);
    }

    return 0;
}

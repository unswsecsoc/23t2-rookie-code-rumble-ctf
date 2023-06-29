#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 64

static const char *QUOTES[] = {
    "Stupidity got us into this mess - why can't it get us out?\n\n",
    "What does \"it\" mean in the sentence \"What time is it?\"?\n\n",
    "All generalizations are false, including this one.\n\n",
    "You can't have everything. Where would you put it?\n\n",
    "You've got mail!\n\n"
};

void flag(void) {
    FILE *file = fopen("flag.txt", "r");

    if (file == NULL) {
        printf("[!] Could not find the flag file.\n");
    }

    else {
        char *flag = NULL;
        size_t len = 0;
        getline(&flag, &len, file);
        printf("%s\n", flag);
        free(flag);
    }
}

char* read(char *prompt, char *buffer, int length) {
    printf(prompt);
    char *result = fgets(buffer, length, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    return result;
}

int main(void) {
    char administrator = 0;
    char username[SIZE] = {0};
    char line[SIZE] = {0};

    setvbuf(stdout, NULL, _IONBF, 0);

    printf(
        " ____________________________________________________________________________________________________ \n"
        "< Welcome to the Alliance for Liberation from Interstellar Enemy Networks (A.L.I.E.N) Supercomputer! >\n"
        " ---------------------------------------------------------------------------------------------------- \n"
        "        \\   ^__^\n"
        "         \\  (oo)\\_______\n"
        "            (__)\\       )\\/\\\n"
        "                ||----w |\n"
        "                ||     ||\n\n"
    );

    read("Username: ", username, SIZE);
    printf("Type \"help\" for a list of commands.\n\n");

    while (read("> ", line, SIZE) != NULL) {
        if (strcmp(line, "whoami") == 0) {
            printf("Username: ");
            printf(username);
            printf("\n");

            printf("Administrator level: ");
            printf("%hhu", administrator);
            printf("\n\n");
        }

        else if (strcmp(line, "update") == 0) {
            read("New username: ", username, SIZE);
            printf("\n");
        }

        else if (strcmp(line, "quote") == 0) {
            int checksum = 0;

            for (char *cursor = username; *cursor; cursor++) {
                checksum += *cursor % 5;
            }

            if (administrator) {
                flag();
            } else {
                printf(QUOTES[checksum % (sizeof(QUOTES) / sizeof(char*))]);
            }
        }

        else if (strcmp(line, "debug") == 0) {
            printf("%p %p %p\n\n", username, line, &administrator);
        }

        else if (strcmp(line, "help") == 0) {
            printf("whoami: Print out your current username.\n");
            printf("update: Change your username.\n");
            printf("quote: Get a quote associated with your username.\n");
            printf("debug: Print out some debugging information (for aliens only).\n");
            printf("help: Print this help message.\n");
            printf("exit: Exit the program.\n\n");
        }

        else if (strcmp(line, "exit") == 0) {
            break;
        }

        else {
            printf("Unrecognised command.\n\n");
        }
    }

    return 0;
}

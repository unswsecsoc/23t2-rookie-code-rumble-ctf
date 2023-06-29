#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

typedef struct {
    // Some people might be nefarious and try
    // to enter more than 16 digits, so have
    // some extra space here just in case.
    char digits[32];
} card;

void here_is_the_flag(void);
void read_from_stdin(char*);
card extract_le_monies(void);

void environment_setup(void);
void signal_handler(int, siginfo_t*, void*);

int main(void) {
    environment_setup();

    printf("John Wick has gone broke and needs your help to save Fortnite from alien invaders!\n");
    printf("Enter the 16 numbers on the front of your credit card: ");

    card money = extract_le_monies();
    int checksum = 0;

    for (int i = 0; i < 15; i++) {
        int digit = money.digits[i];
        checksum += digit + (digit * (i % 2 == 0));
    }

    if (checksum % 10 != 0) {
        printf("This doesn't seem like a valid credit card...\n");
        return 1;
    }

    printf("John Wick sends his regards. Thank you for saving Fortnite!\n");
    return 0;
}

void here_is_the_flag(void) {
    FILE *file = fopen("flag.txt", "r");

    if (file == NULL) {
        printf("[!] Could not open the flag file.\n");
        exit(1);
    }

    char *flag = NULL;
    size_t len = 0;
    getline(&flag, &len, file);

    printf("%s", flag);
    free(flag);
    exit(0);
}

void read_from_stdin(char *output) {
    int input;

    while ((input = getchar()) != EOF && input != '\n') {
        *output++ = (char) input;
    }

    *output = '\0';
}

card extract_le_monies(void) {
    card money;
    read_from_stdin(money.digits);
    return money;
}

void environment_setup(void) {
    setvbuf(stdout, NULL, _IONBF, 0);

    struct sigaction action;
    action.sa_sigaction = &signal_handler;
    action.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV, &action, NULL);
    sigaction(SIGBUS, &action, NULL);
}

void signal_handler(int signal, siginfo_t *info, void *context) {
    ucontext_t *processor = (ucontext_t*) context;

    // NOTE: printf() isn't async-signal-safe, but I cannot be
    // arsed to write custom non-allocating printing code.
    // If something goes wrong here, just run the executable again.
    printf("\n");
    printf("[!] A segmentation fault has occurred.\n");
    printf("[!] Program execution can no longer continue.\n");
    printf("\n");

    printf("[!] Executable function addresses:\n");
    printf("[!]     - main: 0x%lx\n", &main);
    printf("[!]     - here_is_the_flag: 0x%lx\n", &here_is_the_flag);
    printf("[!]     - read_from_stdin: 0x%lx\n", &read_from_stdin);
    printf("[!]     - extract_le_monies: 0x%lx\n", &extract_le_monies);
    printf("[!]     - environment_setup: 0x%lx\n", &environment_setup);
    printf("[!]     - signal_handler: 0x%lx\n", &signal_handler);
    printf("\n");

    printf("[!] Current processor state:\n");
    printf("[!]     - rax: 0x%lx\n", processor->uc_mcontext.gregs[REG_RAX]);
    printf("[!]     - rbx: 0x%lx\n", processor->uc_mcontext.gregs[REG_RBX]);
    printf("[!]     - rcx: 0x%lx\n", processor->uc_mcontext.gregs[REG_RCX]);
    printf("[!]     - rdx: 0x%lx\n", processor->uc_mcontext.gregs[REG_RDX]);
    printf("[!]     - rsi: 0x%lx\n", processor->uc_mcontext.gregs[REG_RSI]);
    printf("[!]     - rdi: 0x%lx\n", processor->uc_mcontext.gregs[REG_RDI]);
    printf("[!]     - rsp: 0x%lx\n", processor->uc_mcontext.gregs[REG_RSP]);
    printf("[!]     - rbp: 0x%lx\n", processor->uc_mcontext.gregs[REG_RBP]);
    printf("[!]     -  r8: 0x%lx\n", processor->uc_mcontext.gregs[REG_R8]);
    printf("[!]     -  r9: 0x%lx\n", processor->uc_mcontext.gregs[REG_R9]);
    printf("[!]     - r10: 0x%lx\n", processor->uc_mcontext.gregs[REG_R10]);
    printf("[!]     - r11: 0x%lx\n", processor->uc_mcontext.gregs[REG_R11]);
    printf("[!]     - r12: 0x%lx\n", processor->uc_mcontext.gregs[REG_R12]);
    printf("[!]     - r13: 0x%lx\n", processor->uc_mcontext.gregs[REG_R13]);
    printf("[!]     - r14: 0x%lx\n", processor->uc_mcontext.gregs[REG_R14]);
    printf("[!]     - r15: 0x%lx\n", processor->uc_mcontext.gregs[REG_R15]);
    printf("[!]     - rip: 0x%lx\n", processor->uc_mcontext.gregs[REG_RIP]);
    exit(1);
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define BOARD_WIDTH 10
#define BOARD_LEN 10
#define NUM_SHIPS 5

struct coord {
	int x;
	int y;
};

struct coord ships[NUM_SHIPS] = {0};

long init();
void print_board();
void print_flag();
struct coord get_coords();
bool hit(struct coord guess);
bool valid_coords(struct coord guess);

int main() {
	unsigned char board[BOARD_WIDTH][BOARD_LEN];
	int remaining_guesses = NUM_SHIPS;
	int ships_hit = 0;

	printf("Welcome to our state of the art combat simulator!\n");
	printf("We'll be testing your combat capabilities - get going!\n");

	fflush(stdout);

	init(board);

	while (remaining_guesses) {
		print_board(board);

		printf("Enter target coords: ");
		struct coord target = get_coords();
		printf("Firing at x: %x, y: %x\n", target.x ,target.y);

		if (valid_coords(target) == false) {
			continue;	
		}

		if (hit(target)) {
			board[target.y][target.x] = 'X';		
			ships_hit++;
		} else {
			board[target.y][target.x] = 'O';		
		}

		remaining_guesses--;
	}
		
	print_board(board);

	if (ships_hit == NUM_SHIPS) {
		print_flag();
	} else {
		printf("Looks like you ain't built for these stars!\n");
	}
}

long init(unsigned char board[BOARD_WIDTH][BOARD_LEN]) {
	setvbuf(stdout, NULL, _IONBF, 0);
	memset(board, '-', BOARD_WIDTH * BOARD_LEN);

	time_t t = time(NULL);
	srand(t);

	printf("The time is %x\n", &t);

	for (int i = 0 ; i < NUM_SHIPS ; ) {
retry:
		ships[i].x = rand() % 10;
		ships[i].y = rand() % 10;

		for (int j = 0 ; j < i ; j++) {
			if (ships[j].x == ships[i].x && ships[j].y == ships[i].y) {
				goto retry;
			}
		}

		i++;
	}

}

struct coord get_coords() {
	long x, y;

	scanf("%d %d",&x, &y);

	//Flush remaining input
	for( long c = getchar() ;c != '\n' ; c = getchar()) {}

	struct coord s =  { .x = x, .y = y };
	return s;
}

void print_board(unsigned char board[BOARD_WIDTH][BOARD_LEN]) {
	for (int i = 0 ; i < BOARD_LEN ; i++) {
		for (int j = 0 ; j < BOARD_WIDTH ; j++) {
			printf("%c", board[i][j]);	
		}
		printf("\n");	
	}
}

bool valid_coords(struct coord guess) {
	if (guess.x < 0 || guess.x > 10) {
		return false;
	} else if (guess.y < 0 || guess.y > 10) {
		return false;
	} else {
		return true;
	}
}

bool hit(struct coord guess) {
	for (int i = 0 ; i < NUM_SHIPS ;i++) {
		if (ships[i].x == guess.x && ships[i].y == guess.y) {
			ships[i].x = -1;
			ships[i].y = -1;

			return true;
		}
	}

	return false;
}

void print_flag() {
	printf("Congrats, you've passed the simulation!\n");

	FILE * f = fopen("flag", "r");

	if (f == NULL) {
		printf("Flag file not found - if this occurs on server, please contact the organizers!\n");
	}

	char buf[32];
	fgets(buf, 32, f);

	printf("%s\n", buf);
}


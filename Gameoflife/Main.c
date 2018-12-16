#include <stdio.h>

#define MAX_HEIGHT_SIZE 70
#define MIN_HEIGHT_SIZE 10
#define MAX_WIDTH_SIZE 70
#define MIN_WIDTH_SIZE 10
#define PLAYER_COLOR 'R'
#define COMPUTER_COLOR 'G'
/*
Ilay Tzuberi

'a'=97 'A'=65
'z'=122 'Z'=90
*/

void initGame(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int* width, int* height, long int* generations);
void initBoard(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int* width, int* height);
void initLivingCells(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height);
void playGame(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, long int generations);
void processBoard(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height);
void getDimentions(int* width, int* height);
void printBoard(const char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height);
long int getNumOfGenerations();
int endstate(const char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height);
char processcell(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int x, int y);

int main()
{
	char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE];
	int width, height;
	long int generations;
	initGame(board, &width, &height, &generations);
	playGame(board, width, height, generations);
	system("pause");
	return 0;
}

void getDimentions(int* width, int* height)
{
	do
	{
		printf("Enter width (10-70):\n");
		scanf("%d", width);
	} while (*width > MAX_WIDTH_SIZE || *width < MIN_WIDTH_SIZE);
	do
	{
		printf("Enter height (10-70):\n");
		scanf("%d", height);
	} while (*height > MAX_HEIGHT_SIZE || *height < MIN_HEIGHT_SIZE);
}

long int getNumOfGenerations()
{
	long int generations;
	do
	{
		printf("Enter number of generations(>0):\n");
		scanf("%ld", &generations);
	} while (generations<=0);
	return generations;
}

void initBoard(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int* width, int* height)
{
	int i, j;
	getDimentions(width, height);
	board[*height][*width];
	for (i = 0; i < *height; i++)
	{
		for (j = 0; j < *width; j++)
		{
			board[i][j] = '-';
		}
	}
	initLivingCells(board, *width, *height);
	printBoard(board, *width, *height);
}

void initLivingCells(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height)
{
	int x, y, i, amount, valid;
	char c;
	do
	{
		printf("Enter number of living cells (0-%d):\n", width*height);
		scanf("%d", &amount);
	} while (amount<0 || amount>width*height);
	for (i = 0; i < amount; i++)
	{
		do
		{
			valid = 0;
			printf("Enter x y and color (R/G):\n");
			scanf("%d %d %c", &x, &y, &c);
			if (c == (PLAYER_COLOR + 32) || c == PLAYER_COLOR)
				valid = 1, c = 'R';
			else if (c == (COMPUTER_COLOR + 32) || c == COMPUTER_COLOR)
				valid = 1, c = 'G';
		} while (x >= width || x < 0 || y >= height || y < 0 || valid == 0);
		board[y][x] = c;
	}

}

void initGame(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int* width, int* height, long int* generations)
{
	printf("Welcome to the game of life!\nSettings:\n");
	initBoard(board, width, height);
	*generations = getNumOfGenerations();
}

void playGame(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, long int generations)
{
	printf("\nWelcome to the game of life!\nThis is the initial board:\n");
	processBoard(board, width, height);
	printBoard(board, width, height);
}

void printBoard(const char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height)
{///prints the board
	int i,j;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			printf("%c", board[j][i]);
		}
		printf("\n");
	}
}

char processcell(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int x, int y)
{
	int nx, ny, player = 0, computer = 0, alive = 0, sum;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			nx = (width + x + i) % width;//new x
			ny = (height + y + j) % height;//new y
			if (j == 0 && i == 0)
				alive = (board[ny][nx] == PLAYER_COLOR || board[ny][nx] == COMPUTER_COLOR);
			else
			{
				if (board[ny][nx] == PLAYER_COLOR)
					player++;
				else if (board[ny][nx] == COMPUTER_COLOR)
					computer++;
			}
		}
	}
	sum = player + computer;
	if (alive && (sum == 3 || sum == 2))
	{
		return board[y][x];
	}
	else
	{
		if (sum == 3)
			return player > computer ? PLAYER_COLOR : COMPUTER_COLOR;
		else
			return '-';
	}
}

void processBoard(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height)
{
	int i, j;
	char temp[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE];
	for ( i = 0; i < height; i++)
	{
		for ( j = 0; j < width; j++)
		{
			temp[i][j] = processcell(board, width, height, j, i);
		}
	}
	board = temp;
}

int endstate(const char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height)
{///returns 0 for extinction, 1 for player win, 2 for computer win
	int player = 0, computer = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (board[i][j] == PLAYER_COLOR)
				player++;
			else if (board[i][j] == COMPUTER_COLOR)
				computer++;
		}
	}
	return (player == 0 && computer == 0) ? 0 : (player > computer ? 1 : (player < computer ? 2 : 0));
}
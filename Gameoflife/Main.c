#include <stdio.h>
#include <stdlib.h>

#define MAX_HEIGHT_SIZE 70
#define MIN_HEIGHT_SIZE 10
#define MAX_WIDTH_SIZE 70
#define MIN_WIDTH_SIZE 10
#define PLAYER_COLOR 'R'
#define COMPUTER_COLOR 'G'
/*
Ilay Tzuberi

note to self: * on a int* will give the value of the pointer
a=97 A=65
z=122 Z=90
*/

void initGame(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int generations);
void initBoard(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int* width, int* height);
void initLivingCells(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height);
void playGame(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int generations);
void processBoard(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height);
void getDimentions(int* width, int* height);
void printBoard(const char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height);
long int getNumOfGenerations();
int endstate(const char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height);
void getCell(int* x, int* y, char* c, int max_x, int min_x, int max_y, int min_y);

int main()
{
	char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE];
	int width, height;
	int generations;
	initGame(board, &width, &height, &generations);  
	//playGame(board, width, height, generations);
	system("pause");
	return 0;
}

void getDimentions(int* width, int* height)
{
	do
	{
		printf("Enter width (10-70):\n");
		scanf("%d", width);
	} while (*width>70 || *width < 10);
	do
	{
		printf("Enter height (10-70):\n");
		scanf("%d", height);
	} while (*height > 70 || *height < 10);
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
		scanf("%d",&amount);
	} while (amount<0 || amount>width*height);
	for (i = 0; i < amount; i++)
	{
		do
		{
			valid = 0;
			printf("Enter x y and color (R/G):\n");
			scanf("%d %d %c", &x, &y, &c);
			if (c == 'r' || c == 'R')
				valid = 1, c = 'R';
			else if(c == 'g' || c == 'G')
				valid = 1, c = 'G';
		} while (x >= width || x < 0 || y >= height || y < 0||valid==0);
		board[x][y] = c;
	}

}

void initGame(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int* width, int* height, int* generations)
{
	printf("Welcome to the game of life!\nSettings:\n");
	initBoard(board, &width, &height);
}

void printBoard(const char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height)
{///prints the board
	int i,j;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			printf("%c", board[i][j]);
		}
		printf("\n");
	}
}

void getCell(int* x, int* y, char* c, int max_x, int min_x, int max_y, int min_y)
{///gets a valid cell from the user
	do
	{
		printf("Enter x y and color (R/G):\n");
		scanf("%d %d %c", x, y, c);
	} while (*x >= max_x || *x < min_x || *y >= max_y || *y < min_y || *c != PLAYER_COLOR || *c != COMPUTER_COLOR);
}
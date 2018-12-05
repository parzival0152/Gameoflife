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
*/

void initGame(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int generations);
void initBoard(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int* width, int* height);
void playGame(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int generations);
void processBoard(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height);
void getDimentions(int* width, int* height);
long int getNumOfGenerations();

int main()
{
	char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE];  
	int width, height;  
	int generations;

	initGame(board, width, height, generations);  
	playGame(board, width, height, generations);
	return 0;
}
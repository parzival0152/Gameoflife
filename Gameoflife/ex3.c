#include <stdio.h>

#define MAX_HEIGHT_SIZE 70
#define MIN_HEIGHT_SIZE 10
#define MAX_WIDTH_SIZE 70
#define MIN_WIDTH_SIZE 10
#define PLAYER_COLOR 'R'
#define PLAYER_COLOR_LOWERCASE 'r'
#define COMPUTER_COLOR 'G'
#define COMPUTER_COLOR_LOWERCASE 'g'
#define DEAD_COLOR '-'

/*******************
Ilay Tzuberi
211873286
83-120-05
********************/

//func decleration mega-block
#pragma region func declerations

void initGame(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int* width, int* height, long int* generations);
void initBoard(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int* width, int* height);
void initLivingCells(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height);
void playGame(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, long int generations);
void processBoard(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height);
void getDimentions(int* width, int* height);
void printBoard(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height);
long int getNumOfGenerations();
int endState(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height);
char processCell(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int x, int y);
void getCell(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height,int allowoverride);
void getTurn(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int* x, int* y);
void ComputerTurn(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int* x, int* y);
void CountNeighbours(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int x, int y, int* neighboar_player, int* neighboar_computer);
void gameEnd(int state, int isthistheend, int* flag);

#pragma endregion
//these gragma blocks are for minimizing the code blocks so the code will be nicer to look at

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

/***************************************************************************************
Function name: getDimentions
Input: pointers to width and height.
Output: none
The function operation: get the numbers
****************************************************************************************/
///the numbers mason what do the mean
void getDimentions(int* width, int* height)
{
	do
	{
		printf("Enter width (10-70):\n");
		scanf("%d", width);
	} while (*width > MAX_WIDTH_SIZE || *width < MIN_WIDTH_SIZE);//makes sure width is within bounds
	do
	{
		printf("Enter height (10-70):\n");
		scanf("%d", height);
	} while (*height > MAX_HEIGHT_SIZE || *height < MIN_HEIGHT_SIZE);//makes sure height is within bounds
}

/***************************************************************************************
Function name: getNumOfGenerations
Input: none.
Output: the number of generations as long int
The function operation: get the number
****************************************************************************************/
long int getNumOfGenerations()
{
	long int generations;
	do
	{
		printf("Enter number of generations(>=0):\n");
		scanf("%ld", &generations);
	} while (generations<0);//makes sure generation number is positive
	return generations;
}

/***************************************************************************************
Function name: initBoard
Input: the board and pointers to width, height.
Output: none
The function operation: fills the board with dead cells
****************************************************************************************/
void initBoard(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int* width, int* height)
{
	int i, j;
	getDimentions(width, height);//get dimantions of board
	for (i = 0; i < *height; i++)
	{
		for (j = 0; j < *width; j++)
		{
			board[i][j] = DEAD_COLOR;
		}
	}//fill the board with dead cells
	///so much death so sad much cry *sad doge face*
	initLivingCells(board, *width, *height);//starts living cells
	printBoard(board, *width, *height);//prints for good mesure
}

/***************************************************************************************
Function name: initLivingCells
Input: the board, the height and the width.
Output: none
The function operation: gets the amount of living cells and fills the board acourdingly
****************************************************************************************/
void initLivingCells(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height)
{
	int i, amount;
	do
	{
		printf("Enter number of living cells (0-%d):\n", width*height);
		scanf("%d", &amount);//gets amount of living cells
	} while (amount<0 || amount>width*height);//make sure amout of cells if plausible
	for (i = 0; i < amount; i++)
	{
		getCell(board, width, height, 0);
	}//get that amount
	printf("\n");
}

/***************************************************************************************
Function name: initGame
Input: the board and pointers for the width, height, genetarions.
Output: none
The function operation: initialize the game using other functions.
****************************************************************************************/
void initGame(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int* width, int* height, long int* generations)
{
	printf("Welcome to the game of life!\nSettings:\n");
	initBoard(board, width, height);//init the board
	*generations = getNumOfGenerations();//get generations
}

/***************************************************************************************
Function name: playGame
Input: the board, the height, the width and the number of generations.
Output: none this is the game loop
The function operation: runs the game following the instructions
****************************************************************************************/
void playGame(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, long int generations)
{
	int state,flag;
	int x, y, i;
	printf("\nWelcome to the game of life!\nThis is the initial board:\n");
	//from here
	processBoard(board, width, height);
	printBoard(board, width, height);
	state = endState(board,width,height);
	gameEnd(state, 0, &flag);
	if (flag)
		return;
	//to here is the code block that checks who won the game
	//the 0 in the center means that there are still turns left to play
	for (i = 0; i < generations; i++)
	{//running over the number of henerations
		if (i % 2 == 0)
		{//the player goes first
			getTurn(board, width, height, &x, &y);
			board[x][y] = PLAYER_COLOR;
		}
		else
		{//the computer goes second
			ComputerTurn(board, width, height, &x, &y);
			board[y][x] = COMPUTER_COLOR;
			printf("G is playing\n%d %d\n", x, y);
		}
		//after every turn
		state = endState(board, width, height);//calculate the state of the game
		if (state == 0 || state == 1 || state == 2)//if someone is totaly dead
		{
			printBoard(board, width, height);//print the board
			gameEnd(state, 0, &flag);//print the victory mesegge
			return;//stop the game
		}
		processBoard(board, width, height);//update the board
		printBoard(board, width, height);//print it
		state = endState(board, width, height);//check the end state
		gameEnd(state, 0, &flag);//check if someone won
		if (flag)//if someone had won
			return;//stop the game
	}
	gameEnd(state, 1, &flag);//there are no more generations check with 1 this time
}

/***************************************************************************************
Function name: printBoard
Input: the board, the height and the width.
Output: none
The function operation: prints the board
****************************************************************************************/
void printBoard(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height)
{///prints the board
	int i,j;
	for (i = 0; i < height; i++)//loop over all the board
	{
		for (j = 0; j < width; j++)
		{
			printf("%c", board[j][i]);//print every cell
		}
		printf("\n");//after every row go down a line
	}
	printf("\n");
}

/***************************************************************************************
Function name: processCell
Input: the board, the height and the width, x and y of chosen cell.
Output: the color of the cells depending on his neighbors
The function operation: the function rus over the 3x3 grid surrounding the cell and using the rules return the state of the cell after 1 genetarion.
****************************************************************************************/
char processCell(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int x, int y)
{
	int nx, ny, player = 0, computer = 0, alive = 0, sum;
	int i, j;
	for (i = -1; i <= 1; i++)
	{
		for (j = -1; j <= 1; j++)
		{
			nx = (width + x + i) % width;//new x
			ny = (height + y + j) % height;//new y
			/*
			new_x and new_y will correct themself if they go out of bounds
			(width + x + i) % width will always be >=0 and <width
			(height + y + j) % height will always be >=0 and <height  
			*/
			if (j == 0 && i == 0)
				alive = (board[ny][nx] != DEAD_COLOR);//check if the cell is alive
			else
			{
				if (board[ny][nx] == PLAYER_COLOR)
					player++;//sum the player colored cells
				else if (board[ny][nx] == COMPUTER_COLOR)
					computer++;//sum the computer colored cells
			}
		}
	}//these loops sum over the grid of squares around them
	sum = player + computer;
	if (alive)
	{//if hes alive
		if (sum == 3 || sum == 2)
			return board[y][x];//if there are enougth people around stay alive
		else
			return DEAD_COLOR;//die of over/under population
	}//if the cell is alive and isnt overpopulated he survives
	else
	{//if hes dead
		if (sum == 3)
			//if he has exactly 3 cells nearby
			return player > computer ? PLAYER_COLOR : COMPUTER_COLOR;
			//if he has more player_color then he will be player_colored else he will be computer_colored
		else
			return DEAD_COLOR;
	}
}

/***************************************************************************************
Function name: processBoard
Input: the board, the height and the width.
Output: none (the function updates the board)
The function operation: run over all cells and updates them to the next generation then copies over the array.
****************************************************************************************/
void processBoard(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height)
{
	int i, j;
	char temp[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE];
	for ( i = 0; i < height; i++)
	{//run over the whole board
		for ( j = 0; j < width; j++)
		{
			temp[i][j] = processCell(board, width, height, j, i);//write to a new board the cells of its location after 1 generation
		}
	}
	for (i = 0; i < height; i++)
	{//run over the whole board again
		for (j = 0; j < width; j++)
		{
			board[i][j] = temp[i][j];//copy over the changed board
		}
	}
}

/***************************************************************************************
Function name: endState
Input: the board, the height and the width.
Output: an int based on scenarios documented in the function itself.
The function operation: calculate who has won.
****************************************************************************************/
int endState(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height)
{
	int player = 0, computer = 0;
	int i, j;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)//nested loop to sum the amount of living cells of each color
		{
			if (board[i][j] == PLAYER_COLOR)
				player++;
			else if (board[i][j] == COMPUTER_COLOR)
				computer++;
		}
	}
	if (player + computer == 0)
		return 0;//both are dead return 0;
	else if (player != 0 && computer == 0)
		return 1;//copmuter is dead player has won return 1
	else if (player == 0 && computer != 0)
		return 2;//player is dead coputer has one return 2
	else if (player > computer)
		return 3;//this is for end game if player has more living cells then computer return 3
	else if (computer > player)
		return 4;//this is for end game if computer has more living cells then player return 4
	else
		return 5;//no end conditions have been met return 5
}

/***************************************************************************************
Function name: getCell
Input: the board, the height and the width, and allowoverride boolean
Output: None (colors the cell he gets fro the user).
The function operation: get a cell from the user and put it into the board.
****************************************************************************************/
void getCell(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int allowoverride)
{	//allowoverride = 0 => no writing over existing cells
	// allowoverride = 1 => write over existing cells
	int x, y;//x,y for input
	char c;//char for input
	int valid, inboard, isalive = 0;//boolean variables for logic
	do
	{
		valid = 0, isalive = 0;
		printf("Enter x y and color (R/G):\n");
		scanf("%d %d %c", &x, &y, &c);
		if (c == PLAYER_COLOR_LOWERCASE || c == PLAYER_COLOR)
			valid = 1, c = PLAYER_COLOR;
		else if (c == COMPUTER_COLOR_LOWERCASE || c == COMPUTER_COLOR)
			valid = 1, c = COMPUTER_COLOR;
		inboard = !(x > width || x < 0 || y > height || y < 0);//checking if the location he chose is not out of bounds
		if (inboard)
			isalive = (board[y][x] != DEAD_COLOR);
	} while (valid == 0 || !inboard || !(!isalive||allowoverride));//will continue to ask for units untill getting a valid input
	/*
	when (!isalive||allowoverride) is true we can write to the board
	when inboard we know the loaction the user chose is on the board
	valid is to check if he inputed a valid cell
	*/
	board[y][x] = c;
}

/***************************************************************************************
Function name: getTurn
Input: the board, the height and the width, and pointers to the next move location (x,y).
Output: None (puts valid values into x and y).
The function operation: get the next move from the player.
****************************************************************************************/
void getTurn(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height,int* x,int* y)
{
	printf("R is playing\nx y:\n");
	scanf("%d %d", y, x);//we know the player enters valid cells
	return;
}

/***************************************************************************************
Function name: ComputerTurn
Input: the board, the height and the width, and pointers to the computer next move location (x,y).
Output: None (puts valid values into x and y).
The function operation: cauclate the next move the computer will make.
****************************************************************************************/
void ComputerTurn(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int* x, int* y) 
{
	int i, j;
	int localX[2] = { 0,0 }, localY[2] = { 0,0 };
	int flag[2] = { 0,0 };
	int playerNeighbours = 0, computerNeighbours = 0;
	//computer scans the board from the top left to the bottom right
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			// read the commnets above about CountNeighbours
			CountNeighbours(board, width, height, i, j, &playerNeighbours, &computerNeighbours);
			//look for the first player cell with 2 or 3 neighbours, and return the location
			if (board[i][j] == PLAYER_COLOR &&
				(playerNeighbours + computerNeighbours == 2 || playerNeighbours + computerNeighbours == 3)) 
			{
				*x = i;
				*y = j;
				return;
			}
			//look for the first dead cell with 2 or 3 neighbours that are mostly belong to the player, and remember it
			if (board[i][j] == DEAD_COLOR && playerNeighbours > computerNeighbours && !flag[0] &&
				(playerNeighbours + computerNeighbours == 2 || playerNeighbours + computerNeighbours == 3)) 
			{
				localX[0] = i;
				localY[0] = j;
				flag[0] = 1;
			}
			//look for the first player cell, and remember it
			if (board[i][j] == PLAYER_COLOR && !flag[1]) 
			{
				localX[1] = i;
				localY[1] = j;
				flag[1] = 1;
			}

		}
	}
	// if we are here, we didn't found player cell with 2 or 3 neighbours

	// if we found dead cell with 2 or 3 neighbours that are mostly belong to the player, we return the location
	if (flag[0]) 
	{
		*x = localX[0];
		*y = localY[0];
		return;
	}
	// if we are here, we didn't found dead cell with 2 or 3 neighbours that are mostly belong to the player

	// we return the location of the first player cell
	*x = localX[1];
	*y = localY[1];
}

/***************************************************************************************
Function name: CountNeighbours
Input: the board, the height and the width, x & y of the cohsen cell, pointers to neighboar_player and neighboar_computer.
Output: none
The function operation: scan over all neighboars and write to the pointers the amout of each one
****************************************************************************************/
void CountNeighbours(char board[MAX_HEIGHT_SIZE][MAX_WIDTH_SIZE], int width, int height, int x, int y, int* neighboar_player, int* neighboar_computer)
{
	int nx, ny, player = 0, computer = 0, alive = 0;
	int i, j;
	for (i = -1; i <= 1; i++)
	{
		for (j = -1; j <= 1; j++)
		{
			nx = (width + x + i) % width;//new x
			ny = (height + y + j) % height;//new y
			/*
			new_x and new_y will correct themself if they go out of bounds
			*/
			if (j == 0 && i == 0)
				alive = board[ny][nx] != DEAD_COLOR;
			else
			{
				if (board[ny][nx] == PLAYER_COLOR)
					player++;
				else if (board[ny][nx] == COMPUTER_COLOR)
					computer++;
			}
		}
	}//these loops sum over the grid of squares around them
	*neighboar_player = player;
	*neighboar_computer = computer;
	//writing to the pointers
	return;
}

/***************************************************************************************
Function name: ganeEnd
Input: the game state, if this is the end of the game(no more generations) and a pointer flag.
Output: none 
The function operation: handels deciding who wins or loses.
****************************************************************************************/
void gameEnd(int state, int isthistheend, int* flag)
{
	if (isthistheend)
	{//if the game is over
		if (state == 3 || state == 1)
		{//either player has more cells then computer or computer is totaly dead
			*flag = 1;
			printf("Game over! %c is the winner :)\n", PLAYER_COLOR);
			return;
		}
		else if (state == 4 || state == 2)
		{//either computer has more cells then player or player is totaly dead
			*flag = 1;
			printf("Game over! %c is the winner :(\n", COMPUTER_COLOR);
			return;
		}
	}
	else
	{//the game isnt over
		if (state == 0)
		{//every body is dead
			*flag = 1;
			printf("Game over! There is no winner :|\n");
			return;
		}
		else if (state == 1)
		{//computer is totaly dead
			*flag = 1;
			printf("Game over! %c is the winner :)\n", PLAYER_COLOR);
			return;
		}
		else if (state == 2)
		{//player is totaly dead
			*flag = 1;
			printf("Game over! %c is the winner :(\n", COMPUTER_COLOR);
			return;
		}
	}
	*flag = 0;//no win condition is met
	return;
}
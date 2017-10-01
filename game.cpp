// Tic Tac Toe game built using decision trees and a backpropagation like algo

#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

// Representing a game state
struct node
{
	char board[3][3];
	char player1;
	char cpu;
};

// Initialize the board
void inboard (char board[3][3])
{
	for (int i = 0;i<3;i++)
		for (int j = 0;j<3;j++)
			board[i][j] = '.';
}

// printing the board
void print(char board[3][3])
{
	for (int i = 0;i<3;i++)
	{
		cout << endl;
		for (int j = 0;j<3;j++)
		{
			cout<<"  ";
			cout<<board[i][j];
		}
	}
	cout<<endl<<endl;
}

// check if the current state is the winning state
char check(char board[3][3])
{
	// horizontal, vertical & diagonal through [0][0]
	if (board[0][0] != '.' && (board[0][0] == board[0][1] && board[0][0] == board[0][2] ||
		board[0][0] == board[1][0] && board[0][0] == board[2][0] ||
		board[0][0] == board[1][1] && board[0][0] == board[2][2]))
						return board[0][0];

	// horizontal, vertical & diagonal through [1][1]
	if (board[1][1] != '.' && (board[1][1] == board[1][0] && board[1][1] == board[1][2] ||
		board[1][1] == board[0][1] && board[1][1] == board[2][1] ||
		board[1][1] == board[2][0] && board[1][1] == board[0][2]))
						return board[1][1];

	// horizontal, vertical & diagonal through [2][2]
	if (board[2][2] != '.' && (board[2][2] == board[0][2] && board[2][2] == board[1][2] ||
		board[2][2] == board[2][0] && board[2][2] == board[2][1]))
						return board[2][2];
	return 0;
}

// compute the score for determining the best move using a decision tree(traced from the in-memory call stack) and a backpropagation like algo to determine the next move
int score(char board[3][3], char player1, char player2)
{
	int bestmove = -9999;
	int movescore = 0;
	if (check(board)==player1)
		return 1000;
	else if (check(board)==player2)
		return -1000;
	for (int r = 0;r<3;r++)
		for (int c = 0;c<3;c++)
			if (board[r][c]=='.')
			{
				board[r][c] = player1;
				movescore = -(score(board, player2, player1));
				board[r][c] = '.';
				if (movescore>=bestmove)
					bestmove = movescore;
			}
	if (bestmove==-9999 || bestmove==0)
		return 0;
	else if (bestmove<0)
		return ++bestmove;
	else if (bestmove>0)
		return --bestmove;
}

// Initialize the base scores and pick the best move
int pickmove(char board[3][3], char player1, char player2)
{
	int bestmove = -9999;
	int bestrow = -9999;
	int bestcol = -9999;
	int movescore = 0;
	for (int r = 0;r<3;r++)
		for (int c = 0;c<3;c++)
			if (board[r][c]=='.')
			{
				board[r][c] = player1;
				movescore = -(score(board, player2, player1));
				board[r][c] = '.';
				if (movescore>=bestmove)
				{
					bestmove = movescore;
					bestrow = r;
					bestcol = c;
				}
			}
	return (10*bestrow+bestcol);
}

// Interacting with the user for input
void placement(char board[3][3], char player)
{
	while (1)
	{
		string r, c;
		int row = 0, col = 0;
		while (1)
		{
			cout<<"Enter the row: ";
			cin>>r;
			row = atoi(r.c_str());
			if (row>=1 && row<=3)
				break;
			cout<<"Invalid Input (try between 1 and 3).\n";
		}
		while (1)
		{
			cout << "Enter the column: ";
			cin >> c;
			col = atoi(c.c_str());
			if (col>=1 && col<=3)
				break;
			cout << "Invalid Input (try between 1 and 3).\n";
		}
		if (board[row-1][col-1] == '.')
		{
			board[row-1][col-1] = player;
			break;
		}
		else
			cout<<"location already occupied, try again\n\n";
	}
}

// Initialize the characters of the cpu
char cpuchoice (char player1)
{
	char cpu;
	cout << "Can you beat me?\n";
	if (player1 == 'x' || player1 == 'X')
		cpu = 'o';
	else
		cpu = 'x';
	return cpu;
}

// Initialize the characters of the player
char playerchoice (string s)
{
	while (1)
	{
		string choice;
		cout<<s<<": What would you like your character to be?\n";
		cin>>choice;
		if (choice.size()>1)
		{
			cout<<"Invalid input. Please try again.\n";
			continue;
		}
		cout<<endl;
		return choice[0];
	}
}

// Initialize the game
void play (char board[3][3], char player1, char cpu)
{
	int moves = 0;
	while (moves<9)
	{
		placement(board, player1);
		moves++;
		print(board);
		if (check(board))
		{
			cout<<player1<<" won!\n\n";
			return;
		}
	  if (moves == 9)
		{
			  cout<<"It's a draw\n\n";
				break;
		}
		int nmove = pickmove(board, cpu, player1);
		int row = nmove/10;
		int col = nmove%10;
		board[row][col] = cpu;
		moves++;
		print(board);
		if (check(board))
		{
			cout<<cpu<<" wins!\n\n";
			return;
		}
	}
}

int main()
{
	node game;
	game.player1 = playerchoice("Player 1");
	game.cpu = cpuchoice(game.player1);
	char x;
	while(1)
	{
		inboard(game.board);
		print(game.board);
		play(game.board, game.player1, game.cpu);
		cout<<"Play another game ? ('y' for yes, any other key to exit)\n";
		cin>>x;
		if(x!='y')
		{
			cout<<"\n";
			return 0;
		}
	}
}

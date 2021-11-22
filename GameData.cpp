#include "GameData.h"

GameData::GameData(int x, int y, int m)
{
	x_dimension = x;
	y_dimension = y;
	total_mines = m;
	mine_board.resize(x);
	play_board.resize(x);
	calculated.resize(x);
	for(int row = 0; row < x; ++row)
	{
		mine_board[row].resize(y);
		play_board[row].resize(y);
		calculated[row].resize(y);
		for(int col = 0; col < y; ++col)
		{
			calculated[row][col] = false;
		}
	}
}

int GameData::set_flag(int x, int y)
{
	if(x > x_dimension || y > y_dimension || x < 1 || y < 1) return 0;

	int row = x - 1, col = y - 1;
	if(calculated[row][col] == true) return 0;
	if(play_board[row][col] == 'X')
	{
		play_board[row][col] = 'F';
		return -1;
	}
	else
	{
		play_board[row][col] = 'X';
		return 1;
	}
}

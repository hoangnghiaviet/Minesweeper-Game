#include "GameData.h"

//Ham se dem so min xung quanh 1 o^
//x la hoanh do, y la tung do cua 1 phan tu mang
//Cac o^ xung quanh 1 o^ duoc ki hieu theo bieu do:
/*
			NW    N    NE
			  \   |   /
			   \  |  /
			W----Cell---E
			   /  |  \
			  /   |   \
			SW    S    SE
*/
int GameData::mine_count(int x, int y) {
	int num_mines = 0;
	//Northwest
	if (x - 1 >= 0 && y - 1 >= 0 && mine_board[x - 1][y - 1] == 'M') {
		++num_mines;
	}
	//West
	if (x - 1 >= 0 && mine_board[x - 1][y] == 'M') {
		++num_mines;
	}
	//Southwest
	if (x - 1 >= 0 && y + 1 < y_dimension && mine_board[x - 1][y + 1] == 'M') {
		++num_mines;
	}
	//South
	if (y + 1 < y_dimension && mine_board[x][y + 1] == 'M') {
		++num_mines;
	}
	//Southeast
	if (x + 1 < x_dimension && y + 1 < y_dimension && mine_board[x + 1][y + 1] == 'M') {
		++num_mines;
	}
	//East
	if (x + 1 < x_dimension && mine_board[x + 1][y] == 'M') {
		++num_mines;
	}
	//Northeast
	if (x + 1 < x_dimension && y - 1 >= 0 && mine_board[x + 1][y - 1] == 'M') {
		++num_mines;
	}
	//North
	if (y - 1 >= 0 && mine_board[x][y - 1] == 'M') {
		++num_mines;
	}
	return num_mines;
}

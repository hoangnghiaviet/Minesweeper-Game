#include "GameData.h"

//Ham se dem so co` xung quanh 1 o^
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
int GameData::flag_count(int x, int y) {
	int num_flags = 0;
	//Northwest
	if (x - 1 >= 0 && y - 1 >= 0 && play_board[x - 1][y - 1] == 'F') {
		++num_flags;
	}
	//West
	if (x - 1 >= 0 && play_board[x - 1][y] == 'F') {
		++num_flags;
	}
	//Southwest
	if (x - 1 >= 0 && y + 1 < y_dimension && play_board[x - 1][y + 1] == 'F') {
		++num_flags;
	}
	//South
	if (y + 1 < y_dimension && play_board[x][y + 1] == 'F') {
		++num_flags;
	}
	//Southeast
	if (x + 1 < x_dimension && y + 1 < y_dimension && play_board[x + 1][y + 1] == 'F') {
		++num_flags;
	}
	//East
	if (x + 1 < x_dimension && play_board[x + 1][y] == 'F') {
		++num_flags;
	}
	//Northeast
	if (x + 1 < x_dimension && y - 1 >= 0 && play_board[x + 1][y - 1] == 'F') {
		++num_flags;
	}
	//North
	if (y - 1 >= 0 && play_board[x][y - 1] == 'F') {
		++num_flags;
	}
	return num_flags;
}

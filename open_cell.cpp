#include "GameData.h"

//Ham se tra ve false neu o^ duoc mo la min, va tra ve true cho cac truong hop con lai
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
bool GameData::open_cell(int x, int y) {
	if (x < 0 || x >= x_dimension || y < 0 || y >= y_dimension) {
		return true;
	}
	if (play_board[x][y] == 'F' || calculated[x][y] == true) {
		return true;
	}
	if (mine_board[x][y] == 'M') {
		return false;
	}

	calculated[x][y] = true;
	++num_moves;
	int num_mines = mine_count(x, y);
	if (num_mines != 0) {
		play_board[x][y] = num_mines + 48;
	}
	//Neu so min cua 1 o^ = 0 thi mo nhung o^ xung quanh
	else {
		play_board[x][y] = '0';
		//Northwest
		open_cell(x - 1, y - 1);

		//West
		open_cell(x - 1, y);

		//Southwest
		open_cell(x - 1, y + 1);

		//South
		open_cell(x, y + 1);

		//Southeast
		open_cell(x + 1, y + 1);

		//East
		open_cell(x + 1, y);

		//Northeast
		open_cell(x + 1, y - 1);

		//North
		open_cell(x, y - 1);
	}
	return true;
}

#include "GameData.h"

GameData::GameData(int x, int y, int m) : x_dimension(x), y_dimension(y), total_mines(m), num_moves_max(x* y - m) {
	for (int i = 0; i < x_dimension; ++i) {
		std::vector<bool>col(y_dimension, false);
		calculated.push_back(col);
	}

	for (int i = 0; i < x_dimension; ++i) {
		std::vector<char>col(y_dimension, 'X');
		play_board.push_back(col);
	}

	for (int i = 0; i < x_dimension; ++i) {
		std::vector<char>col(y_dimension, 'X');
		mine_board.push_back(col);
	}
	std::vector<char>mine_pos(x_dimension * y_dimension, false);
	int num_mines = 0;
	while (num_mines < total_mines) {
		int pos = rand() % (x_dimension * y_dimension);
		if (mine_pos[pos] == false) {
			mine_pos[pos] = true;
			int col = pos / y_dimension, row = pos % y_dimension;
			mine_board[col][row] = 'M';
			++num_mines;
		}
	}
}

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

bool GameData::open_cell(int x, int y) {
	if (x < 0 || x >= x_dimension || y < 0 || y >= y_dimension) {
		return false;
	}
	if (play_board[x][y] == 'F' || calculated[x][y] == true) {
		return false;
	}
	if (mine_board[x][y] == 'M') {
		return true;
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
	return false;
}

int GameData::open_nearby_cells(int x, int y) {
	if (calculated[x][y] == false || flag_count(x, y) != mine_count(x, y)) {
		return -1;
	}

	//Northwest
	bool b1 = open_cell(x - 1, y - 1);

	//West
	bool b2 = open_cell(x - 1, y);

	//Southwest
	bool b3 = open_cell(x - 1, y + 1);

	//South
	bool b4 = open_cell(x, y + 1);

	//Southeast
	bool b5 = open_cell(x + 1, y + 1);

	//East
	bool b6 = open_cell(x + 1, y);

	//Northeast
	bool b7 = open_cell(x + 1, y - 1);

	//North
	bool b8 = open_cell(x, y - 1);

	bool isGameOver = b1 || b2 || b3 || b4 || b5 || b6 || b7 || b8;
	if (isGameOver) {
		return 1;
	}
	else {
		return 0;
	}
}

void GameData::set_flag(int x, int y) {
	if (calculated[x][y] == true) {
		return;
	}
	if (play_board[x][y] == 'X') {
		play_board[x][y] = 'F';
	}
	else {
		play_board[x][y] = 'X';
	}
}

void GameData::update_play_board() {
	for (int i = 0; i < x_dimension; ++i) {
		for (int j = 0; j < y_dimension; ++j) {
			if (mine_board[i][j] == 'M') {
				play_board[i][j] = 'M';
			}
		}
	}
}

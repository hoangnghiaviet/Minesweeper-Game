#include "GameData.h"

GameData::GameData(int x, int y, int m) : x_dimension(x), y_dimension(y), total_mines(m), num_moves_max(x* y - m) {
	for (int i = 0; i < x_dimension; ++i) {
		vector<bool>col(y_dimension, false);
		calculated.push_back(col);
	}

	for (int i = 0; i < x_dimension; ++i) {
		vector<char>col(y_dimension, 'X');
		play_board.push_back(col);
	}

	for (int i = 0; i < x_dimension; ++i) {
		vector<char>col(y_dimension, 'X');
		mine_board.push_back(col);
	}
	vector<char>mine_pos(x_dimension * y_dimension, false);
	int num_mines = 0;
	srand(time(0));
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

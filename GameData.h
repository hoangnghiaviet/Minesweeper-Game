#pragma once

#include <vector>
#include <string>
#include <ctime>
#include <iostream>
using namespace std;

class GameData {
public:
	int x_dimension = 0, y_dimension = 0, total_mines = 0, num_moves = 0, num_moves_max = 0;
	vector<vector<char>>mine_board, play_board;
	vector<vector<bool>>calculated;

	int mine_count(int x, int y);
	int flag_count(int x, int y);

	GameData() = default;
	GameData(int, int, int);

	bool open_cell(int x, int y);
	bool open_nearby_cells(int x, int y);
	int set_flag(int x, int y);
};

#pragma once
#include <bits/stdc++.h>
using namespace std;

class GameData {
private:
	int x_dimension = 0, y_dimension = 0, total_mines = 0, num_moves = 0, num_moves_max = 0;
	vector<vector<char>> mine_board, play_board;
	vector<vector<bool>> calculated;

	int mine_count(int x, int y);
	int flag_count(int x, int y);

public:
	GameData() = default;

	GameData(int x, int y, int m);

	bool open_cell(int x, int y);

	bool open_nearby_cell(int x, int y);

	int set_flag(int x, int y);
};

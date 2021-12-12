#pragma once

#include <vector>
#include <string>
#include <ctime>
#include <iostream>

class GameData {
private:
	int x_dimension = 0, y_dimension = 0, total_mines = 0;
	int num_moves = 0, num_moves_max = 0;
	int num_flags = 0;

	std::vector<std::vector<char>>mine_board, play_board;
	std::vector<std::vector<bool>>calculated;

	int mine_count(int x, int y);
	int flag_count(int x, int y);

public:
	GameData() = default;
	GameData(int, int, int);

	bool open_cell(int x, int y);
	int open_nearby_cells(int x, int y);
	void set_flag(int x, int y);

	void update_play_board();

	int return_num_moves() {
		return num_moves;
	}

	friend class GameWindow;
	friend void LoadGameWindow(unsigned, unsigned, unsigned, bool);
};

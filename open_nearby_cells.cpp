#include "GameData.h"

//Hoat dong dua tren open_cell
bool GameData::open_nearby_cells(int x, int y) {
	if (calculated[x][y] == false) {
		return true;
	}
	if (flag_count(x, y) != mine_count(x, y)) {
		return true;
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

	return (b1 && b2 && b3 && b4 && b5 && b6 && b7 && b8);
}

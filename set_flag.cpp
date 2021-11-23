#include "GameData.h"

// Ham tra ve 0 neu khong co flag nao duoc them hoac xoa
// Ham tra ve 1 neu co flag bi xoa
// Ham tra ve -1 neu co flag duoc dat
// Cac gia tri 0, 1, -1 duoc dung de tinh so luong bom con lai tren bang

int GameData::set_flag(int x, int y)
{
	if(x >= x_dimension || y >= y_dimension || x < 0 || y < 0) return 0;

	if(calculated[x][y] == true) return 0;
	if(play_board[x][y] == 'X')
	{
		play_board[x][y] = 'F';
		return -1;
	}
	else
	{
		play_board[x][y] = 'X';
		return 1;
	}
}

#include "StartGameMenu.h"

// Function will open the window with corresponding window_number

void move_to_start_game_menu(int window_number)
{
    switch(window_number)
    {
        case 0:
            // LoadGameWindow();
            break;
        case 1:
            // NewGameWindow();
            break;
        case 2:
            // LeaderBoardWindow();
            break;
        case 3:
            // InstructionWindow();
            break;
        case 4:
            // AuthorWindow();
            break;
        default:
            break;
    }
}

#include "StartGameMenu.h"

// Function will open the window with corresponding window_number
void openSelectedWindow(int window_number)
{
    switch (window_number)
    {
    case 0:
        // LoadGameWindow();
        break;
    case 1:
        NewGameWindow();
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
    }
}

//void LoadGameWindow();

void NewGameWindow()
{
    GameWindow board(16, 16, 40);
    board.initBoard();
    board.loadTexture();

    sf::Clock clock;

    // run the main loop
    while (board.isWindowOpen()) {

        // handle events
        board.pollEvent();

        // update the board
        if (!board.isGameEnded()) {
            board.update();

            sf::Time time_elapsed = clock.getElapsedTime();
            board.updateClock(time_elapsed);
        }

        // draw the board
        board.render();
    }
}

//void LeaderBoardWindow();

//void InstructionWindow();

//void AuthorWindow();
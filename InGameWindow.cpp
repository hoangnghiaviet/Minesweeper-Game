#include "InGameWindow.h"

void InGameWindow(unsigned width, unsigned height, unsigned num_mines)
{
    GameWindow board(width, height, num_mines);
    board.initBoard();
    board.loadTexture();

    sf::Clock clock;

    //Run the main loop
    while (board.isWindowOpen()) {

        //Handle events
        board.pollEvent();

        //Update the board
        if (!board.isGameEnded()) {
            board.update();

            sf::Time time_elapsed = clock.getElapsedTime();
            board.updateClock(time_elapsed);
        }

        //Draw the board
        board.render();
    }
}

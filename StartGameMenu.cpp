#include "StartGameMenu.h"

// Function will open the window with corresponding window_number
void openSelectedWindow(int window_number)
{
    switch (window_number)
    {
    case 0:
        LoadGameWindow();
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

void LoadGameWindow() {
    std::ifstream input("save_game.txt");

    float time_elapsed;
    unsigned width, height, num_mines;
    int num_moves;
    std::vector<std::vector<bool>>calculated;
    std::vector<std::vector<char>>mine_board, play_board;

    //Load previous game
    input >> time_elapsed
        >> width >> height
        >> num_moves >> num_mines;

    for (unsigned i = 0; i < width; ++i) {
        std::vector<bool>col;
        for (unsigned j = 0; j < height; ++j) {
            bool tmp; input >> tmp;
            col.push_back(tmp);
        }
        calculated.push_back(col);
    }
    for (unsigned i = 0; i < width; ++i) {
        std::vector<char>col;
        for (unsigned j = 0; j < height; ++j) {
            char tmp; input >> tmp;
            col.push_back(tmp);
        }
        mine_board.push_back(col);
    }
    for (unsigned i = 0; i < width; ++i) {
        std::vector<char>col;
        for (unsigned j = 0; j < height; ++j) {
            char tmp; input >> tmp;
            col.push_back(tmp);
        }
        play_board.push_back(col);
    }

    GameWindow board(width, height, num_mines);
    board.initBoard();
    board.loadTexture();

    //Set up time elapsed
    board.time_elapsed = sf::seconds(time_elapsed);

    //Set up game data
    board.game_data->num_moves = num_moves;
    board.game_data->calculated = calculated;
    board.game_data->mine_board = mine_board;
    board.game_data->play_board = play_board;
    board.updateBoard();

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

    input.close();
}

void NewGameWindow()
{
    //NewGameWindow should give the player the options to change the below values
    unsigned width = 5, height = 5, num_mines = 5;

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

//void LeaderBoardWindow();

//void InstructionWindow();

//void AuthorWindow();
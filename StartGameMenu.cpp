#include "StartGameMenu.h"
#include "StartGameWindow.h"

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

    bool isValidSave;
    float time_elapsed;
    unsigned width, height, num_mines;
    int num_moves, score;
    std::vector<std::vector<bool>>calculated;
    std::vector<std::vector<char>>mine_board, play_board;

    input >> isValidSave;

    //If there is not a valid game save, direct the player back to StartGameWindow()
    if (!isValidSave) {
        sf::RenderWindow window(sf::VideoMode(1080, 720), "MineSweeper", sf::Style::Titlebar | sf::Style::Close);

        sf::Texture background_t;
        background_t.loadFromFile("game_texture/Image/background.jpg");

        sf::Sprite background;
        background.setTexture(background_t);

        sf::Font font;
        font.loadFromFile("game_texture/Font/AppleII.ttf");

        sf::Text message;
        message.setFont(font);
        message.setCharacterSize(24);
        message.setFillColor(sf::Color::Black);
        //Put the message in the center
        message.setPosition(sf::Vector2f(540.f - 360.f, 360 - 30.f));
        message.setString("No game saves are found! Press Esc to return to menu.");

        while (window.isOpen()) {
            sf::Event ev;
            while (window.pollEvent(ev)) {
                switch (ev.type) {

                case sf::Event::Closed: {
                    window.close();
                }
                case sf::Event::KeyPressed: {
                    if (ev.key.code == sf::Keyboard::Escape) {
                        window.close();
                        StartGameWindow();
                    }
                }
                }
            }

            window.clear(sf::Color::Black);

            window.draw(background);
            window.draw(message);

            window.display();
        }

        return;
    }

    //Load previous game
    input >> time_elapsed >> score
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

    input.close();

    GameWindow board(width, height, num_mines);
    board.initBoard();
    board.loadTexture();

    //Set up the saved time elapsed
    board.prev_time_elapsed = sf::seconds(time_elapsed);

    //Set up the saved score
    board.loadSavedScore(score);
    board.current_num_moves = num_moves;

    //Set up the saved game data
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
        else {
            //Delete the data for games that have been won or lost
            board.saveCurrentGame();
        }

        //Draw the board
        board.render();
    }
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
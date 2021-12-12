#include "GameWindow.h"
#include "StartGameWindow.h"

//Initialize the board
void GameWindow::initBoard() {

    //Load the texture for a default cell
    default_t.loadFromFile("game_texture/Cell/default.png");

    //Load font
    font.loadFromFile("game_texture/Font/AppleII.ttf");

    sf::Vector2f cellSize = sf::Vector2f(32.f, 32.f);
    float startPos_x = static_cast<float>(540 - (width * 32) / 2);
    float startPos_y = static_cast<float>(360 - (height * 32) / 2);

    //Populate the 2d cells array
    for (unsigned i = 0; i < height; ++i) {
        for (unsigned j = 0; j < width; ++j) {
            sf::RectangleShape cell;
            cell.setSize(sf::Vector2f(cellSize.x, cellSize.y));
            cell.setPosition(sf::Vector2f(j * cellSize.x + startPos_x, i * cellSize.y + startPos_y));
            cell.setTexture(&default_t);
            cells.push_back(cell);
        }
    }

    //Set up the background
    background_t.loadFromFile("game_texture/Image/ingame_background.jpg");
    background.setTexture(background_t);

    //Set up the clock
    clock.setFont(font);
    clock.setCharacterSize(24);
    clock.setFillColor(sf::Color::Black);
    clock.setPosition(sf::Vector2f(startPos_x, startPos_y - 36.f));

    //Set up the number of remaining mines
    remaining_mines.setFont(font);
    remaining_mines.setCharacterSize(24);
    remaining_mines.setFillColor(sf::Color::Black);
    remaining_mines.setPosition(sf::Vector2f(startPos_x + cellSize.x * (width - 1), startPos_y - 36.f));
    remaining_mines.setString(std::to_string(game_data->total_mines));

    //Set up the game ending message
    end_message.setFont(font);
    end_message.setCharacterSize(24);
    end_message.setFillColor(sf::Color::Black);
    end_message.setPosition(sf::Vector2f(482.f, startPos_y - 98.f));

    //Set up replay game
    replay_button_texture.loadFromFile("game_texture/Image/replay_button.png");
    replay_button.setSize(sf::Vector2f(20.f, 20.f));
    replay_button.setTexture(&replay_button_texture);
    replay_button.setPosition(sf::Vector2f(530.f, startPos_y - 60.f));
}

//Load the texture for each type of cell
void GameWindow::loadTexture() {
    t_pack.resize(11);
    t_pack[0].loadFromFile("game_texture/Cell/0.png");
    t_pack[1].loadFromFile("game_texture/Cell/1.png");
    t_pack[2].loadFromFile("game_texture/Cell/2.png");
    t_pack[3].loadFromFile("game_texture/Cell/3.png");
    t_pack[4].loadFromFile("game_texture/Cell/4.png");
    t_pack[5].loadFromFile("game_texture/Cell/5.png");
    t_pack[6].loadFromFile("game_texture/Cell/6.png");
    t_pack[7].loadFromFile("game_texture/Cell/7.png");
    t_pack[8].loadFromFile("game_texture/Cell/8.png");
    t_pack[9].loadFromFile("game_texture/Cell/flag.png");
    t_pack[10].loadFromFile("game_texture/Cell/mine.png");
}

bool GameWindow::isGameEnded() {
    return isGameLost || isGameWon;
}

//Handle the event polling
void GameWindow::pollEvent() {
    sf::Event ev;
    while (window.pollEvent(ev)) {
        switch (ev.type) {

        case sf::Event::Closed: {
            saveCurrentGame();
            window.close();
            StartGameWindow();
        }
        case sf::Event::KeyPressed: {
            if (ev.key.code == sf::Keyboard::Escape) {
                saveCurrentGame();
                window.close();
                StartGameWindow();
            }
        }
        }
    }
}

//Update whenever there is a mouse click on a cell
void GameWindow::update() {
    //Get the mouse coordinates
    sf::Vector2i mousePosWindow = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosView = window.mapPixelToCoords(mousePosWindow);

    //Illuminate a cell if the mouse is hovering on the cell
    for (int i = 0; i < cells.size(); ++i) {
        if (cells[i].getGlobalBounds().contains(mousePosView)) {
            cells[i].setFillColor(sf::Color::Cyan);
        }
        else {
            cells[i].setFillColor(sf::Color::White);
        }
    }

    //Left mouse button -> Open a cell or open nearby cells
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        for (int i = 0; i < cells.size(); ++i) {
            if (cells[i].getGlobalBounds().contains(mousePosView)) {
                int x = i % width, y = i / width;

                int game_state = (*game_data).open_nearby_cells(x, y);
                switch (game_state) {
                case 1:
                    isGameLost = true;
                    updateBoard();
                    break;
                case 0:
                    updateBoard();
                    break;
                case -1:
                    //Open a cell
                    isGameLost = (*game_data).open_cell(x, y);
                    updateBoard();
                    break;
                }
            }
        }
    }

    //Right mouse button -> Set flag
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        if (isMouseHeld == false) {

            isMouseHeld = true;

            for (int i = 0; i < cells.size(); ++i) {
                if (cells[i].getGlobalBounds().contains(mousePosView)) {
                    int x = i % width, y = i / width;

                    (*game_data).set_flag(x, y);
                    updateBoard();
                    updateRemainingMines();
                }
            }
        }
    }
    else {
        isMouseHeld = false;
    }

    //If game is won, merge the play_board and mine_board, print the winning message and save the score
    if (game_data->num_moves == game_data->num_moves_max) {
        isGameWon = true;
        updateBoard();

        saveCurrentScore();
    }

    //If game is ended, print out the game ending message
    if (this->isGameEnded()) {
        if (isGameWon) {
            end_message.setString("You win!");
        }
        else {
            end_message.setString("You lose");
        }
    }
}

//Check if player want to play again or not when game is ended
bool GameWindow::isReplay() {
    sf::Vector2i mousePosWindow = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosView = window.mapPixelToCoords(mousePosWindow);

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if(replay_button.getGlobalBounds().contains(mousePosView)) {
            window.close();
            return true;
        }
    }
    return false;
}

//Update the clock
void GameWindow::updateClock(sf::Time new_time_elapsed) {
    time_elapsed = new_time_elapsed + prev_time_elapsed;
    clock_text = convertToString(time_elapsed.asSeconds());
    clock.setString(clock_text);
}

void GameWindow::saveCurrentScore() {
    int level, num_mines = game_data->total_mines;
    if (width == 9 && height == 9 && num_mines == 10) {
        level = 0;
    }
    else if (width == 16 && height == 16 && num_mines == 40) {
        level = 1;
    }
    else if (width == 30 && height == 16 && num_mines == 99) {
        level = 2;
    }
    // If the game is in custom mode, we will not update the high scores list
    else {
        return;
    }
    std::ifstream input("high_scores.txt");

    std::vector<float>scores;
    for (int i = 0; i < 12; ++i) {
        float tmp; input >> tmp;
        scores.push_back(tmp);
    }

    input.close();

    // Insert the current score into the high scores list
    // --------------------------------------------------
    float currentScore = time_elapsed.asSeconds();

    int i = 0, score_size = 4;
    for (; i < score_size; ++i) {
        if (scores[score_size * level + i] == 0) {
            scores[score_size * level + i] = currentScore;
            break;
        }
    }
    if (i < score_size) {
        sort(scores.begin() + score_size * level, scores.begin() + score_size * level + i + 1);
    }
    else {
        if (scores[score_size * level + 3] > currentScore) {
            scores[score_size * level + 3] = currentScore;
            sort(scores.begin() + score_size * level, scores.begin() + score_size * level + score_size);
        }
    }

    std::ofstream output("high_scores.txt", std::ofstream::out | std::ofstream::trunc);

    for (int i = 0; i < 12; ++i) {
        output << scores[i] << '\n';
    }

    output.close();

}

//Handle the rendering of entities
void GameWindow::render() {

    window.clear();
    window.draw(background);

    window.draw(clock);
    window.draw(remaining_mines);

    for (auto& cell : cells) {
        window.draw(cell);
    }

    if (this->isGameEnded()) {
        window.draw(end_message);
    }

    if(isReplayButton) {
        window.draw(replay_button);
    }

    window.display();
}

void GameWindow::saveCurrentGame() {
    std::ofstream output("save_game.txt", std::ofstream::out | std::ofstream::trunc);
    if (this->isGameEnded()) {
        output << 0;
    }
    else {
        output
            << 1 << '\n'
            << time_elapsed.asSeconds() << '\n'
            << width << ' ' << height << '\n'
            << (*game_data).num_moves << ' ' << (*game_data).total_mines << '\n';

        for (unsigned i = 0; i < width; ++i) {
            for (unsigned j = 0; j < height; ++j) {
                output << (*game_data).calculated[i][j] << ' ';
            }
            output << '\n';
        }
        output << '\n';

        for (unsigned i = 0; i < width; ++i) {
            for (unsigned j = 0; j < height; ++j) {
                output << (*game_data).mine_board[i][j] << ' ';
            }
            output << '\n';
        }
        output << '\n';

        for (unsigned i = 0; i < width; ++i) {
            for (unsigned j = 0; j < height; ++j) {
                output << (*game_data).play_board[i][j] << ' ';
            }
            output << '\n';
        }
    }

    output.close();
}

//Constructors
GameWindow::GameWindow(unsigned i, unsigned j, unsigned k) : width(i), height(j) {
    window.create(sf::VideoMode(1080, 720), "Minesweeper", sf::Style::Titlebar | sf::Style::Close);

    //Initialize game logic
    game_data = new GameData(i, j, k);
}

//Destructors
GameWindow::~GameWindow() {
    delete[] game_data;
}

// Update the text of the number of remaining mines based on player's flags
void GameWindow::updateRemainingMines() {
    int num_remaining_mines = game_data->total_mines - game_data->num_flags;
    if (num_remaining_mines < 0) {
        num_remaining_mines = 0;
    }

    std::string remaining_mines_text;
    if (num_remaining_mines < 10) {
        remaining_mines_text += "0";
    }
    remaining_mines_text += std::to_string(num_remaining_mines);
    remaining_mines.setString(remaining_mines_text);
}

//Update the board whenever a move is made
void GameWindow::updateBoard() {
    if (isGameLost || isGameWon) {
        (*game_data).update_play_board();
    }
    for (int i = 0; i < cells.size(); ++i) {
        int x = i % width, y = i / width;
        switch ((*game_data).play_board[x][y]) {
        case '0':
            cells[i].setTexture(&t_pack[0]);
            break;
        case '1':
            cells[i].setTexture(&t_pack[1]);
            break;
        case '2':
            cells[i].setTexture(&t_pack[2]);
            break;
        case '3':
            cells[i].setTexture(&t_pack[3]);
            break;
        case '4':
            cells[i].setTexture(&t_pack[4]);
            break;
        case '5':
            cells[i].setTexture(&t_pack[5]);
            break;
        case '6':
            cells[i].setTexture(&t_pack[6]);
            break;
        case '7':
            cells[i].setTexture(&t_pack[7]);
            break;
        case '8':
            cells[i].setTexture(&t_pack[8]);
            break;
        case 'F':
            cells[i].setTexture(&t_pack[9]);
            break;
        case 'M':
            cells[i].setTexture(&t_pack[10]);
            break;
        case 'X':
            cells[i].setTexture(&default_t);
            break;
        }
    }
}

// Convert a time value in float to a HH:MM:SS string
// ------------------------------------------------------
std::string convertToString(float time) {
    std::string res;
    if (time >= 60) {
        if (time >= 600) {
            res += std::to_string(static_cast<int>(time / 60)) + ": ";
            time -= static_cast<int>(time / 60) * 60;
        }
        else {
            res += "0";
            res += std::to_string(static_cast<int>(time / 60)) + ": ";
            time -= static_cast<int>(time / 60) * 60;
        }
    }
    else {
        res += "00: ";
    }
    if (time >= 10) {
        res += std::to_string(static_cast<int>(time));
    }
    else {
        res += "0";
        res += std::to_string(static_cast<int>(time));
    }
    return res;
}

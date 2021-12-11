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
    background_t.loadFromFile("game_texture/Image/background.jpg");
    background.setTexture(background_t);

    //Set up the clock
    clock.setFont(font);
    clock.setCharacterSize(24);
    clock.setFillColor(sf::Color::Black);
    clock.setPosition(sf::Vector2f(startPos_x, startPos_y + height * cellSize.y));

    //Set up the score
    score.setFont(font);
    score.setCharacterSize(24);
    score.setFillColor(sf::Color::Black);
    score.setString("Score: 0");
    score.setPosition(sf::Vector2f(startPos_x, startPos_y + height * cellSize.y + 30));

    //Set up the game ending message
    end_message.setFont(font);
    end_message.setCharacterSize(24);
    end_message.setFillColor(sf::Color::Black);
    end_message.setPosition(sf::Vector2f(startPos_x, startPos_y - 35));

    //Set up replay game
    replay_button_texture.loadFromFile("game_texture/Image/replay_button.png");
    replay_button.setSize(sf::Vector2f(20, 20));
    replay_button.setTexture(&replay_button_texture);
    replay_button.setPosition(sf::Vector2f(530, startPos_y - 30));
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

                int game_state = (*game_data).open_nearby_cells(x, y), new_num_moves;
                switch (game_state) {
                case 1:
                    isGameLost = true;
                    updateBoard();
                    break;
                case 0:
                    updateBoard();
                    new_num_moves = (*game_data).return_num_moves();
                    updateScore(new_num_moves);
                    break;
                case -1:
                    //Open a cell
                    isGameLost = (*game_data).open_cell(x, y);
                    updateBoard();

                    int new_num_moves = (*game_data).return_num_moves();
                    updateScore(new_num_moves);

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
            end_message.setString("You win! Press Esc");
        }
        else {
            end_message.setString("You lose! Press Esc");
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

//Convert the elapsed time in float to a HH:MM:SS string
std::string GameWindow::convertToString(float time) {
    std::string res;
    if (time >= 3600) {
        res += std::to_string(static_cast<int>(time / 3600)) + ": ";
        time -= static_cast<int>(time / 3600) * 3600;
    }
    else {
        res += "0: ";
    }
    if (time >= 60) {
        res += std::to_string(static_cast<int>(time / 60)) + ": ";
        time -= static_cast<int>(time / 60) * 60;
    }
    else {
        res += "0: ";
    }
    res += std::to_string(static_cast<int>(time));
    return res;
}

//Update the score based on time elapsed
void GameWindow::updateScore(int new_num_moves) {
    if (new_num_moves > current_num_moves) {
        current_score = static_cast<int>(new_num_moves * 500 * (1 - 0.0005f * time_elapsed.asSeconds()));
        std::string score_text = "Score: " + std::to_string(current_score);
        score.setString(score_text);

        current_num_moves = new_num_moves;
    }
}

void GameWindow::saveCurrentScore() {
    std::ifstream input("high_scores.txt");

    std::vector<int>scores;
    for (int i = 0; i < 10; ++i) {
        int tmp; input >> tmp;
        scores.push_back(tmp);
    }
    scores.push_back(current_score);

    //Sort in descending order
    sort(scores.begin(), scores.end(), std::greater<int>());

    input.close();

    std::ofstream output("high_scores.txt", std::ofstream::out | std::ofstream::trunc);

    //Only print out 5 highest scores
    for (int i = 0; i < 10; ++i) {
        output << scores[i] << '\n';
    }

    output.close();

}

void GameWindow::loadSavedScore(int saved_score) {
    current_score = saved_score;
    std::string score_text = "Score: " + std::to_string(current_score);
    score.setString(score_text);
}

//Handle the rendering of entities
void GameWindow::render() {
    unsigned redVal = static_cast<unsigned>((cos(time_elapsed.asSeconds()) / 4.0 + 0.75f) * 255.f);
    unsigned greenVal = static_cast<unsigned>((sin(time_elapsed.asSeconds()) / 2.0 + 0.5f) * 255.f);
    window.clear(sf::Color(redVal, greenVal, 255));

    //window.draw(background);

    window.draw(clock);
    window.draw(score);

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
            << time_elapsed.asSeconds() << ' ' << current_score << '\n'
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

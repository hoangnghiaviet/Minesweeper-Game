#include "GameWindow.h"

//Initialize the board
void GameWindow::initBoard() {

    //Load the texture for a default cell
    default_t.loadFromFile("game_texture/Cell/default.png");

    //Load font
    font.loadFromFile("game_texture/Font/VNARIAL.ttf");

    sf::Vector2f cellSize = sf::Vector2f(32.f, 32.f);
    unsigned int startPos_x = 540 - (width * 32) / 2;
    unsigned int startPos_y = 350 - (height * 32) / 2;

    //Populate the 2d cells array
    for (unsigned i = 0; i < width; ++i) {
        for (unsigned j = 0; j < height; ++j) {
            sf::RectangleShape cell;
            cell.setSize(sf::Vector2f(cellSize.x, cellSize.y));
            cell.setPosition(sf::Vector2f(i * cellSize.x + startPos_x, j * cellSize.y + startPos_y));
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
    clock.setPosition(startPos_x, startPos_y - 60);

    //Set up the score
    score.setFont(font);
    score.setCharacterSize(24);
    score.setFillColor(sf::Color::Black);
    score.setString("Score: 0");
    score.setPosition(startPos_x, startPos_y - 30);
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

//Handle the event polling
void GameWindow::pollEvent() {
    sf::Event ev;
    while (window.pollEvent(ev)) {
        switch (ev.type) {

        case sf::Event::Closed: {
            window.close();
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

    //Left mouse button -> Open cell
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        for (int i = 0; i < cells.size(); ++i) {
            if (cells[i].getGlobalBounds().contains(mousePosView)) {
                int y = i % height, x = i / height;

                isGameOver = (*game_data).open_cell(x, y);
                updateBoard();

                new_num_moves = (*game_data).return_num_moves();
                updateScore(new_num_moves);
            }
        }
    }

    //Middle mouse button -> Open nearby cells
    if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
        for (int i = 0; i < cells.size(); ++i) {
            if (cells[i].getGlobalBounds().contains(mousePosView)) {
                int y = i % height, x = i / height;

                int game_state = (*game_data).open_nearby_cells(x, y);
                switch (game_state) {
                case 1:
                    isGameOver = true;
                    updateBoard();
                    break;
                case 0:
                    updateBoard();
                    new_num_moves = (*game_data).return_num_moves();
                    updateScore(new_num_moves);
                    break;
                case -1:
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
                    int y = i % height, x = i / height;

                    (*game_data).set_flag(x, y);
                    updateBoard();
                }
            }
        }
    }
    else {
        isMouseHeld = false;
    }
}

//Update the clock
void GameWindow::updateClock(sf::Time new_time_elapsed) {
    time_elapsed = new_time_elapsed;
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

//Handle the rendering of entities
void GameWindow::render() {
    window.clear();

    window.draw(background);

    window.draw(clock);
    window.draw(score);

    for (auto& cell : cells) {
        window.draw(cell);
    }

    window.display();
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
    if (isGameOver) {
        (*game_data).update_play_board();
    }
    for (int i = 0; i < cells.size(); ++i) {
        int y = i % height, x = i / height;
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
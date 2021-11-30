#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameData.h"
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <functional>

class GameWindow {
public:

    //Initialize the board
    void initBoard();

    //Load the texture for each type of cell
    void loadTexture();

    bool isWindowOpen() {
        return window.isOpen();
    }

    bool isGameEnded();

    //Handle the event polling
    void pollEvent();

    //Update whenever there is a mouse click on a cell
    void update();

    //Update the clock
    void updateClock(sf::Time);

    //Convert the elapsed time in float to a HH:MM:SS string
    std::string convertToString(float);

    //Update the score based on time elapsed
    void updateScore(int);

    void saveCurrentScore();

    void loadSavedScore(int);

    //Handle the rendering of entities
    void render();

    void saveCurrentGame();

    //Constructors
    GameWindow() = default;
    GameWindow(unsigned, unsigned, unsigned);

    //Destructors
    ~GameWindow();

    friend void LoadGameWindow();

private:
    //Update the board whenever a move is made
    void updateBoard();

    sf::RenderWindow window;

    //Background
    sf::Sprite background;
    sf::Texture background_t;

    //Board
    std::vector<sf::RectangleShape>cells;

    //Texture pack
    std::vector<sf::Texture> t_pack;
    sf::Texture default_t;

    //Font
    sf::Font font;

    //Clock
    sf::Text clock;
    std::string clock_text = "0:0:0";
    sf::Time time_elapsed = sf::seconds(0.f);
    sf::Time prev_time_elapsed = sf::seconds(0.f);

    //Score
    sf::Text score;
    int current_score = 0;
    int current_num_moves = 0;

    //Game ending message
    sf::Text end_message;

    //Input delay
    bool isMouseHeld = false;

    //Game logic
    unsigned width, height;
    GameData* game_data;
    bool isGameLost = false;
    bool isGameWon = false;

};


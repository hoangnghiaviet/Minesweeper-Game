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

    //Check if player want to play again or not when game is ended
    bool isReplay();

    //Update the clock
    void updateClock(sf::Time);

    void saveCurrentScore();

    //Handle the rendering of entities
    void render();

    void saveCurrentGame();

    //Constructors
    GameWindow() = default;
    GameWindow(unsigned, unsigned, unsigned);

    //Destructors
    ~GameWindow();

    friend void LoadGameWindow(unsigned, unsigned, unsigned, bool);

private:
    void updateRemainingMines();

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

    //The number of remaining mines
    sf::Text remaining_mines;

    //Game ending message
    sf::Text end_message;

    //Input delay
    bool isMouseHeld = false;

    //Game logic
    unsigned width, height;
    GameData* game_data;
    bool isGameLost = false;
    bool isGameWon = false;

    //Game replay
    bool isReplayButton = false;
    sf::Texture replay_button_texture;
    sf::RectangleShape replay_button;
};

// Convert a time value in float to a HH:MM:SS string
// --------------------------------------------------
std::string convertToString(float);

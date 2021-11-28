#include <vector>
#include <string>
#include <ctime>
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

#include "StartGameWindow.h"
#include "ButtonClass.h"
#include "MouseEvent.h"
#include "StartGameMenu.h"

// There are 5 buttons:
// start_game_button[0]: Load game button (move to LoadGameWindow)
// start_game_button[1]: New game button (move to NewGameWindow)
// start_game_button[2]: Leader board button (move to LeaderBoardWindow)
// start_game_button[3]: Instruction button (move to InstructionWindow)
// start_game_button[4]: Author button (move to AuthorWindow)

void StartGameWindow()
{
    RenderWindow start_game_window(VideoMode(600, 600), "MineSweeper", Style::Close);

    // back ground texture
    Texture start_game_background_texture;
    start_game_background_texture.loadFromFile("GameData/Image/start_game_background.jpg");
    Sprite start_game_background;
    start_game_background.setTexture(start_game_background_texture);

    int total_button = 5;

    // button texture
    vector<Texture> button_texture;
    button_texture.resize(total_button);
    for(int i = 0; i < total_button; ++i)
    {
        char number = '0' + i;
        string image_path = "GameData/Image/start_game_button";
        image_path += number;
        image_path += ".jpg";
        button_texture[i].loadFromFile(image_path);
    }

    // button constructor
    vector<ButtonClass> start_game_button;
    start_game_button.resize(total_button);
    for(int i = 0; i < total_button; ++i)
    {
        start_game_button[i] = ButtonClass(Vector2f(200.f, 30.f), Vector2f(200, 270 + i * 50));
        start_game_button[i].button.setTexture(&button_texture[i]);
    }

    // display window
    while(start_game_window.isOpen())
    {
        Event event;
        while(start_game_window.pollEvent(event))
        {
            if(event.type == Event::Closed)
            {
                start_game_window.close();
            }
        }

        int clicked_button = get_button_clicked(start_game_button, total_button, start_game_window);
        if(clicked_button != -1)
        {
            start_game_window.close();
            move_to_start_game_menu(clicked_button);
        }

        start_game_window.clear(Color::White);
        start_game_window.draw(start_game_background);
        for(int i = 0; i < total_button; ++i)
        {
            start_game_window.draw(start_game_button[i].button);
        }
        start_game_window.display();
    }
}

#include <vector>
#include <string>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

#include "StartGameWindow.h"
#include "InGameWindow.h"
#include "ButtonClass.h"
#include "MouseEvent.h"

void StartGameWindow()
{
    RenderWindow start_game_window(VideoMode(600, 600), "MineSweeper", Style::Close);

    // back ground texture
    Texture start_game_background_texture;
    if(!start_game_background_texture.loadFromFile("GameData/Image/start_game_background.jpg"))
    {
        cout << "Background image error";
        return;
    }
    Sprite start_game_background;
    start_game_background.setTexture(start_game_background_texture);

    // button texture
    Texture button_texture[5];
    for(int i = 0; i < 5; ++i)
    {
        char number = '0' + i;
        string image_path = "GameData/Image/start_game_button";
        image_path += number;
        image_path += ".jpg";
        if(!button_texture[i].loadFromFile(image_path))
        {
            cout << "Button image error";
            return;
        }
    }

    // button constructor
    ButtonClass B[5];
    for(int i = 0; i < 5; ++i)
    {
        B[i] = ButtonClass(Vector2f(200.f, 30.f), Vector2f(200, 270 + i * 50));
        B[i].button.setTexture(&button_texture[i]);
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

        string click = get_mouse_clicked();
        Vector2i mouse_position = Mouse::getPosition(start_game_window);
        for(int i = 0; i < 5; ++i)
        {
            if(check_mouse_clicked(mouse_position, B[i].button.getPosition(), B[i].button.getSize()))
            {
                if(click == "left")
                {
                    start_game_window.close();
                }
                B[i].button.setFillColor(Color::Red);
            }
            else B[i].button.setFillColor(Color::White);
        }

        start_game_window.clear(Color::White);
        start_game_window.draw(start_game_background);
        for(int i = 0; i < 5; ++i)
        {
            start_game_window.draw(B[i].button);
        }
        start_game_window.display();
    }
}

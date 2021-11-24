#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

#include "StartGameMenu.h"
#include "StartGameWindow.h"

void NewGameWindow()
{
    RenderWindow new_game_window(VideoMode(600, 600), "MineSweeper", Style::Close);

    while(new_game_window.isOpen())
    {
        Event event;
        while(new_game_window.pollEvent(event))
        {
            if(event.type == Event::Closed)
            {
                new_game_window.close();
                StartGameWindow();
            }
        }

        new_game_window.clear(Color::White);

        new_game_window.display();
    }
}

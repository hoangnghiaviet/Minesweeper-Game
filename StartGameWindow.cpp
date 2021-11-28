#include "StartGameWindow.h"

// There are 5 buttons:
// start_game_button[0]: Load game button (move to LoadGameWindow)
// start_game_button[1]: New game button (move to NewGameWindow)
// start_game_button[2]: Leader board button (move to LeaderBoardWindow)
// start_game_button[3]: Instruction button (move to InstructionWindow)
// start_game_button[4]: Author button (move to AuthorWindow)

void StartGameWindow()
{
    sf::RenderWindow start_game_window(sf::VideoMode(800, 600), "MineSweeper", sf::Style::Titlebar | sf::Style::Close);

    // back ground texture
    sf::Texture start_game_background_texture;
    start_game_background_texture.loadFromFile("game_texture/Image/start_game_background.png");
    sf::Sprite start_game_background;
    start_game_background.setTexture(start_game_background_texture);

    int total_button = 5;

    // button texture
    std::vector<sf::Texture>button_texture;
    button_texture.resize(total_button);
    for (int i = 0; i < total_button; ++i)
    {
        char number = '0' + i;
        std::string image_path = "game_texture/Image/start_game_button";
        image_path += number;
        image_path += ".jpg";
        button_texture[i].loadFromFile(image_path);
    }

    // button constructor
    std::vector<ButtonClass>start_game_button;
    start_game_button.resize(total_button);
    for (int i = 0; i < total_button; ++i)
    {
        start_game_button[i] = ButtonClass(sf::Vector2f(240.f, 30.f), sf::Vector2f(280, 270 + i * 60), button_texture[i]);
    }

    // display window
    while (start_game_window.isOpen())
    {
        sf::Event event;
        while (start_game_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                start_game_window.close();
            }
        }

        int clicked_button = get_button_clicked(start_game_button, total_button, start_game_window);
        if (clicked_button != -1)
        {
            start_game_window.close();
            openSelectedWindow(clicked_button);
        }

        start_game_window.clear(sf::Color::White);

        //draw background
        start_game_window.draw(start_game_background);

        //draw buttons
        for (int i = 0; i < total_button; ++i)
        {
            start_game_window.draw(start_game_button[i].button);
        }

        start_game_window.display();
    }
}

#include "StartGameMenu.h"

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
        InstructionWindow();
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
    RenderWindow new_game_window(VideoMode(800, 600), "MineSweeper", Style::Close);

    // background
    Texture new_game_background_texture;
    new_game_background_texture.loadFromFile("Game_Texture/Image/start_game_background.png");
    Sprite new_game_background;
    new_game_background.setTexture(new_game_background_texture);

    int total_new_game_button = 3;

    vector<Texture> new_game_button_texture;
    new_game_button_texture.resize(total_new_game_button);
    for(int i = 0; i < total_new_game_button; ++i)
    {
        char number = '0' + i;
        string image_path = "Game_Texture/Image/NewGameWindow/new_game_button";
        image_path += number;
        image_path += ".jpg";
        new_game_button_texture[i].loadFromFile(image_path);
    }

    vector<ButtonClass> new_game_button;
    new_game_button.resize(total_new_game_button);
    for(int i = 0; i < total_new_game_button; ++i)
    {
        new_game_button[i] = ButtonClass(Vector2f(240.f, 30.f), Vector2f(280, 270 + i * 60), new_game_button_texture[i]);
    }

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

        int clicked_button = get_button_clicked(new_game_button, total_new_game_button, new_game_window);
        if(clicked_button != -1)
        {
            new_game_window.close();
            switch(clicked_button)
            {
                case 0:
                    InGameWindow(9, 9, 10);
                    break;
                case 1:
                    InGameWindow(16, 16, 40);
                    break;
                case 2:
                    InGameWindow(30, 16, 99);
                    break;
            }
        }

        new_game_window.clear(Color::White);
        new_game_window.draw(new_game_background);
        for(int i = 0; i < total_new_game_button; ++i)
        {
            new_game_window.draw(new_game_button[i].button);
        }
        new_game_window.display();
    }
}

//void LeaderBoardWindow();

void InstructionWindow()
{
    RenderWindow instruction_window(VideoMode(800, 600), "MineSweeper", Style::Close);

    int current_page = 0, total_page = 3;

    vector<Texture> instruction_page_texture;
    instruction_page_texture.resize(total_page);
    for(int i = 0; i < total_page; ++i)
    {
        char number = '0' + i;
        string image_path = "Game_Texture/Image/InstructionWindow/instruction_page";
        image_path += number;
        image_path += ".png";
        instruction_page_texture[i].loadFromFile(image_path);
    }

    vector<Sprite> instruction_page;
    instruction_page.resize(total_page);
    for(int i = 0; i < total_page; ++i)
    {
        instruction_page[i].setTexture(instruction_page_texture[i]);
    }

    //
    CircleShape previous_button(12.f, 3);
    CircleShape next_button(12.f, 3);

    previous_button.setFillColor(Color::White);
    next_button.setFillColor(Color::White);

    previous_button.setOutlineThickness(1.f);
    previous_button.setOutlineColor(Color::Black);
    next_button.setOutlineThickness(1.f);
    next_button.setOutlineColor(Color::Black);

    previous_button.setPosition(Vector2f(85, 567));
    next_button.setPosition(Vector2f(715, 543));

    previous_button.rotate(-90.f);
    next_button.rotate(90.f);

    while(instruction_window.isOpen())
    {
        Event event;
        while(instruction_window.pollEvent(event))
        {
            if(event.type == Event::Closed)
            {
                instruction_window.close();
                StartGameWindow();
            }
        }

        string click = get_mouse_clicked();
        Vector2i mouse_position = Mouse::getPosition(instruction_window);
        if(check_mouse_clicked(mouse_position, Vector2f(85, 546.3), Vector2f(18, 20.7)))
        {
            previous_button.setFillColor(Color::Red);
            if(click == "left")
            {
                current_page = (current_page - 1 + total_page) % total_page;
            }
        }
        else
        {
            previous_button.setFillColor(Color::White);
        }
        if(check_mouse_clicked(mouse_position, Vector2f(697, 543), Vector2f(18, 20.7)))
        {
            next_button.setFillColor(Color::Red);
            if(click == "left")
            {
                current_page = (current_page + 1) % total_page;
            }
        }
        else
        {
            next_button.setFillColor(Color::White);
        }

        instruction_window.clear(Color::White);
        instruction_window.draw(instruction_page[current_page]);
        instruction_window.draw(previous_button);
        instruction_window.draw(next_button);
        instruction_window.display();
    }
}

//void AuthorWindow();

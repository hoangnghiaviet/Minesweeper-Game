#include "StartGameMenu.h"
#include "StartGameWindow.h"
#include "GameWindow.h"

// Function will open the window with corresponding window_number
void openSelectedWindow(int window_number)
{
    switch (window_number)
    {
    case 0:
        LoadGameWindow(1, 1, 1, 1);
        break;
    case 1:
        NewGameWindow();
        break;
    case 2:
        LeaderBoardWindow();
        break;
    case 3:
        InstructionWindow();
        break;
    case 4:
        AuthorWindow();
        break;
    }
}

void LoadGameWindow(unsigned _width, unsigned _height, unsigned _num_mines, bool isLoadGame) {

    bool isValidSave;
    float time_elapsed;
    unsigned width, height, num_mines;
    int num_moves;
    std::vector<std::vector<bool>>calculated;
    std::vector<std::vector<char>>mine_board, play_board;

    if(isLoadGame == true)
    {
        std::ifstream input("save_game.txt");
        input >> isValidSave;

        //If there is not a valid game save, direct the player back to StartGameWindow()
        if (!isValidSave) {
            sf::RenderWindow window(sf::VideoMode(800, 600), "MineSweeper", sf::Style::Titlebar | sf::Style::Close);

            sf::Texture background_t;
            background_t.loadFromFile("game_texture/Image/InstructionWindow/instruction_background.png");

            sf::Sprite background;
            background.setTexture(background_t);

            sf::Font font;
            font.loadFromFile("game_texture/Font/kranky.ttf");

            sf::Text message;
            message.setFont(font);
            message.setCharacterSize(24);
            message.setFillColor(sf::Color::Black);
            //Put the message in the center
            message.setPosition(sf::Vector2f(105.f, 390.f));
            message.setString("No game saves are found! Press Esc to return to menu.");

            while (window.isOpen()) {
                sf::Event ev;
                while (window.pollEvent(ev)) {
                    switch (ev.type) {

                    case sf::Event::Closed: {
                        window.close();
                        StartGameWindow();
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
        input >> time_elapsed
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
    }
    else
    {
        width = _width;
        height = _height;
        num_mines = _num_mines;
    }

    GameWindow board(width, height, num_mines);
    board.initBoard();
    board.loadTexture();

    if(isLoadGame == true)
    {
        //Set up the saved time elapsed
        board.prev_time_elapsed = sf::seconds(time_elapsed);

        //Set up the saved game data
        board.game_data->num_moves = num_moves;
        board.game_data->calculated = calculated;
        board.game_data->mine_board = mine_board;
        board.game_data->play_board = play_board;
        board.updateBoard();
    }

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

            if (board.isReplay()) {
                LoadGameWindow(width, height, num_mines, 0);
                return;
            }
        }
        else {
            //Delete the data for games that have been won or lost
            board.saveCurrentGame();

            if (board.isReplay()) {
                LoadGameWindow(width, height, num_mines, 0);
                return;
            }
        }

        //Draw the board
        board.render();
    }
}

void NewGameWindow()
{
    sf::RenderWindow new_game_window(sf::VideoMode(800, 600), "MineSweeper", sf::Style::Close);

    // background
    sf::Texture new_game_background_texture;
    new_game_background_texture.loadFromFile("Game_Texture/Image/start_game_background.png");
    sf::Sprite new_game_background;
    new_game_background.setTexture(new_game_background_texture);

    int total_new_game_button = 3;

    std::vector<sf::Texture> new_game_button_texture;
    new_game_button_texture.resize(total_new_game_button);
    for (int i = 0; i < total_new_game_button; ++i)
    {
        char number = '0' + i;
        std::string image_path = "Game_Texture/Image/NewGameWindow/new_game_button";
        image_path += number;
        image_path += ".jpg";
        new_game_button_texture[i].loadFromFile(image_path);
    }

    std::vector<ButtonClass> new_game_button;
    new_game_button.resize(total_new_game_button);
    for (int i = 0; i < total_new_game_button; ++i)
    {
        new_game_button[i] = ButtonClass(sf::Vector2f(240.f, 30.f), sf::Vector2f(280.f, static_cast<float>(270 + i * 60)), new_game_button_texture[i]);
    }

    while (new_game_window.isOpen())
    {
        sf::Event event;
        while (new_game_window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed: {
                new_game_window.close();
                StartGameWindow();
            }
            case sf::Event::KeyPressed: {
                if (event.key.code == sf::Keyboard::Escape) {
                    new_game_window.close();
                    StartGameWindow();
                }
            }
            }
        }

        int clicked_button = get_button_clicked(new_game_button, total_new_game_button, new_game_window);
        if (clicked_button != -1)
        {
            new_game_window.close();
            switch (clicked_button)
            {
            case 0:
                LoadGameWindow(9, 9, 10, 0);
                break;
            case 1:
                LoadGameWindow(16, 16, 40, 0);
                break;
            case 2:
                LoadGameWindow(30, 16, 99, 0);
                break;
            }
        }

        new_game_window.clear(sf::Color::White);
        new_game_window.draw(new_game_background);
        for (int i = 0; i < total_new_game_button; ++i)
        {
            new_game_window.draw(new_game_button[i].button);
        }
        new_game_window.display();
    }
}

void LeaderBoardWindow()
{
    sf::RenderWindow leader_board_window(sf::VideoMode(800, 600), "MineSweeper", sf::Style::Close);

    sf::Texture leader_board_background_texture;
    leader_board_background_texture.loadFromFile("Game_Texture/Image/start_game_background.png");
    sf::Sprite leader_board_background;
    leader_board_background.setTexture(leader_board_background_texture);

    sf::Font font;
    font.loadFromFile("Game_Texture/Font/AppleII.ttf");

    // Set up the text indicating levels of difficulty
    // -----------------------------------------------
    std::vector<sf::RectangleShape> levels(3);
    std::vector<sf::Text> levels_text(3);

    for (int i = 0; i < 3; ++i) {
        float x_coord = 80.f + i * (240.f), y_coord = 270.f;

        // Set up the boxes
        levels[i].setSize(sf::Vector2f(160, 30));
        levels[i].setPosition(sf::Vector2f(x_coord, y_coord));
        levels[i].setFillColor(sf::Color::White);

        // Set up the text
        levels_text[i].setFont(font);
        levels_text[i].setCharacterSize(20);
        levels_text[i].setFillColor(sf::Color::Black);

        if (i == 0) {
            levels_text[i].setString("Beginner");
            levels_text[i].setPosition(sf::Vector2f(x_coord + 30, y_coord));
        }
        if (i == 1) {
            levels_text[i].setString("Intermediate");
            levels_text[i].setPosition(sf::Vector2f(x_coord, y_coord));
        }
        if (i == 2) {
            levels_text[i].setString("Expert");
            levels_text[i].setPosition(sf::Vector2f(x_coord + 42, y_coord));
        }
    }

    // Set up the scores
    // -----------------
    int total_score = 12;
    std::vector<sf::RectangleShape> score_sprite(total_score);
    std::vector<sf::Text> score_text(total_score);
    std::ifstream input("high_scores.txt");
    for(int i = 0; i < 12; ++i)
    {
        float x_coord, y_coord = static_cast<float>(30 * (11 + (i % 4) * 2));
        if (i < 4) {
            x_coord = 80.f;
        }
        else if (i < 8) {
            x_coord = 320.f;
        }
        else {
            x_coord = 560.f;
        }

        // Init the score sprite
        score_sprite[i].setSize(sf::Vector2f(160, 30));
        score_sprite[i].setPosition(sf::Vector2f(x_coord, y_coord));
        score_sprite[i].setFillColor(sf::Color::White);

        // Init the score text
        score_text[i].setFont(font);
        score_text[i].setCharacterSize(20);
        score_text[i].setPosition(sf::Vector2f(x_coord, y_coord));
        score_text[i].setFillColor(sf::Color::Black);

        // Set the string of each score text
        float score_f;
        input >> score_f;

        std::string score_string = "#";
        score_string += char('1' + i % 4);
        score_string += ": ";
        score_string += convertToString(score_f);

        score_text[i].setString(score_string);
    }
    input.close();

    // Set up the reset button
    // -----------------------
    sf::Texture reset_button_texture;
    reset_button_texture.loadFromFile("Game_Texture/Image/reset_button.jpg");
    ButtonClass reset_button;
    reset_button = ButtonClass(sf::Vector2f(80, 30), sf::Vector2f(360, 555), reset_button_texture);

    while(leader_board_window.isOpen())
    {
        sf::Event event;
        while(leader_board_window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed: {
                leader_board_window.close();
                StartGameWindow();
            }
            case sf::Event::KeyPressed: {
                if (event.key.code == sf::Keyboard::Escape) {
                    leader_board_window.close();
                    StartGameWindow();
                }
            }
            }
        }

        std::string mouse_click = get_mouse_clicked();
        if(check_mouse_clicked(sf::Mouse::getPosition(leader_board_window), reset_button.button.getPosition(), reset_button.button.getSize()))
        {
            reset_button.button.setFillColor(sf::Color::Red);
            if(mouse_click == "left")
            {
                std::ofstream output("high_scores.txt", std::ofstream::out | std::ofstream::trunc);
                for(int i = 0; i < total_score; ++i)
                {
                    output << 0 << '\n';
                }
                output.close();
                std::ifstream input("high_scores.txt");
                for(int i = 0; i < total_score; ++i)
                {
                    std::string score_string = "#";
                    score_string += char('1' + i % 4);
                    score_string += ": ";
                    score_string += convertToString(0.f);
                    score_text[i].setString(score_string);
                }
                input.close();
            }
        }
        else
        {
            reset_button.button.setFillColor(sf::Color::White);
        }

        leader_board_window.clear(sf::Color::White);
        leader_board_window.draw(leader_board_background);

        // Draw the text indicating levels of difficulty: Beginner, Intermediate, Expert
        for (int i = 0; i < 3; ++i) {
            leader_board_window.draw(levels[i]);
            leader_board_window.draw(levels_text[i]);
        }

        // Draw the score
        for(int i = 0 ; i < total_score; ++i)
        {
            leader_board_window.draw(score_sprite[i]);
            leader_board_window.draw(score_text[i]);
        }

        leader_board_window.draw(reset_button.button);
        leader_board_window.display();
    }
}

void InstructionWindow()
{
    sf::RenderWindow instruction_window(sf::VideoMode(800, 600), "MineSweeper", sf::Style::Close);

    int current_page = 0, total_page = 3;

    std::vector<sf::Texture> instruction_page_texture;
    instruction_page_texture.resize(total_page);
    for (int i = 0; i < total_page; ++i)
    {
        char number = '0' + i;
        std::string image_path = "Game_Texture/Image/InstructionWindow/instruction_page";
        image_path += number;
        image_path += ".png";
        instruction_page_texture[i].loadFromFile(image_path);
    }

    std::vector<sf::Sprite> instruction_page;;
    instruction_page.resize(total_page);
    for (int i = 0; i < total_page; ++i)
    {
        instruction_page[i].setTexture(instruction_page_texture[i]);
    }

    sf::CircleShape previous_button(12.f, 3);
    sf::CircleShape next_button(12.f, 3);

    previous_button.setFillColor(sf::Color::White);
    next_button.setFillColor(sf::Color::White);

    previous_button.setOutlineThickness(1.f);
    previous_button.setOutlineColor(sf::Color::Black);
    next_button.setOutlineThickness(1.f);
    next_button.setOutlineColor(sf::Color::Black);

    previous_button.setPosition(sf::Vector2f(85, 567));
    next_button.setPosition(sf::Vector2f(715, 543));

    previous_button.rotate(-90.f);
    next_button.rotate(90.f);

    while (instruction_window.isOpen())
    {
        sf::Event event;
        while (instruction_window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed: {
                instruction_window.close();
                StartGameWindow();
            }
            case sf::Event::KeyPressed: {
                if (event.key.code == sf::Keyboard::Escape) {
                    instruction_window.close();
                    StartGameWindow();
                }
            }
            }
        }

        std::string click = get_mouse_clicked();
        sf::Vector2i mouse_position = sf::Mouse::getPosition(instruction_window);
        if (check_mouse_clicked(mouse_position, sf::Vector2f(85.f, 546.3f), sf::Vector2f(18.f, 20.7f)))
        {
            previous_button.setFillColor(sf::Color::Red);
            if (click == "left")
            {
                current_page = (current_page - 1 + total_page) % total_page;
            }
        }
        else
        {
            previous_button.setFillColor(sf::Color::White);
        }
        if (check_mouse_clicked(mouse_position, sf::Vector2f(697.f, 543.f), sf::Vector2f(18.f, 20.7f)))
        {
            next_button.setFillColor(sf::Color::Red);
            if (click == "left")
            {
                current_page = (current_page + 1) % total_page;
            }
        }
        else
        {
            next_button.setFillColor(sf::Color::White);
        }

        instruction_window.clear(sf::Color::White);
        instruction_window.draw(instruction_page[current_page]);
        instruction_window.draw(previous_button);
        instruction_window.draw(next_button);
        instruction_window.display();
    }
}

void AuthorWindow()
{
    sf::RenderWindow author_window(sf::VideoMode(800, 600), "MineSweeper", sf::Style::Close);

    // Set up the background
    // ---------------------
    sf::Texture author_background_texture;
    author_background_texture.loadFromFile("Game_Texture/Image/author_background.png");
    sf::Sprite author_background;
    author_background.setTexture(author_background_texture);

    // Set up the text
    // ---------------
    sf::Font font;
    font.loadFromFile("game_texture/Font/kranky.ttf");

    sf::RectangleShape viet_sprite;
    viet_sprite.setSize(sf::Vector2f(280.f, 30.f));
    viet_sprite.setPosition(sf::Vector2f(80.f, 540.f));
    viet_sprite.setFillColor(sf::Color::White);

    sf::Text viet_text;
    viet_text.setFont(font);
    viet_text.setCharacterSize(18);
    viet_text.setFillColor(sf::Color::Black);
    viet_text.setPosition(sf::Vector2f(100.f, 543.f));
    viet_text.setString("21125027 - Hoang Nghia Viet");

    sf::RectangleShape khanh_sprite;
    khanh_sprite.setSize(sf::Vector2f(280.f, 30.f));
    khanh_sprite.setPosition(sf::Vector2f(440.f, 540.f));
    khanh_sprite.setFillColor(sf::Color::White);

    sf::Text khanh_text;
    khanh_text.setFont(font);
    khanh_text.setCharacterSize(18);
    khanh_text.setFillColor(sf::Color::Black);
    khanh_text.setPosition(sf::Vector2f(449.f, 543.f));
    khanh_text.setString("21125046 - Nguyen Tuan Khanh");

    while (author_window.isOpen())
    {
        sf::Event event;
        while (author_window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed: {
                author_window.close();
                StartGameWindow();
            }
            case sf::Event::KeyPressed: {
                if (event.key.code == sf::Keyboard::Escape) {
                    author_window.close();
                    StartGameWindow();
                }
            }
            }
        }

        author_window.clear(sf::Color::White);

        author_window.draw(author_background);

        author_window.draw(viet_sprite);
        author_window.draw(viet_text);
        author_window.draw(khanh_sprite);
        author_window.draw(khanh_text);

        author_window.display();
    }
}

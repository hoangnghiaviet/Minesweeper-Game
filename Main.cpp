#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


class game_data_class {
private:
    Vector2i dimension;
    vector<vector<bool>> del_board;

public:
    vector<vector<Sprite>> board;

    game_data_class() = default;

    game_data_class(Vector2i _dimension)
    {
        dimension.x = _dimension.x;
        dimension.y = _dimension.y;
        del_board.resize(_dimension.x);
        board.resize(_dimension.x);
        for(int row = 0; row < _dimension.x; ++row)
        {
            del_board[row].resize(_dimension.y);
            board[row].resize(_dimension.y);
            for(int col = 0; col < _dimension.y; ++col)
            {
                del_board[row][col] = false;
                board[row][col].setPosition(200 * row, 200 * col);
            }
        }
    }

    void change_del_board(Vector2i _dimension)
    {
        del_board[_dimension.x][_dimension.y] = !del_board[_dimension.x][_dimension.y];
    }

    bool get_del_board(Vector2i _dimension)
    {
        return del_board[_dimension.x][_dimension.y];
    }

    Vector2i get_dimension()
    {
        return dimension;
    }

    void mouse_event(RenderWindow* window)
    {
        bool left_mouse = false;
        while(Mouse::isButtonPressed(Mouse::Left))
        {
            left_mouse = true;
        }
        if(left_mouse == true)
        {
            Vector2i mouse_position = Mouse::getPosition(*window);
            for(int row = 0; row < dimension.x; ++row)
            {
                for(int col = 0; col < dimension.y; ++col)
                {
                    Vector2i upleft = Vector2i(200 * row, 200 * col);
                    Vector2i downright = Vector2i(upleft.x + 200, upleft.y + 200);
                    if(upleft.x < mouse_position.x && mouse_position.x < downright.x && upleft.y < mouse_position.y && mouse_position.y < downright.y)
                    {
                        change_del_board(Vector2i(row, col));
                        return;
                    }
                }
            }
        }
    }
};



int main()
{

    // input data
    Vector2i dimension;
    cin >> dimension.x >> dimension.y;
    Texture _board_texture;
    if(!_board_texture.loadFromFile("Gamedata/Image/playboard.png"))
    {
        cout << "Loading play board image error";
        return 0;
    }

    // constructor
    game_data_class play_board_data {dimension};
    for(int row = 0; row < dimension.x; ++row)
    {
        for(int col = 0; col < dimension.y; ++col)
        {
            play_board_data.board[row][col].setTexture(_board_texture);
        }
    }

    RenderWindow start_game_window(VideoMode(200 * dimension.x, 200 * dimension.y), "In game window");

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

        play_board_data.mouse_event(&start_game_window);

        start_game_window.clear(Color::White);

        for(int row = 0; row < dimension.x; ++row)
        {
            for(int col = 0; col < dimension.y; ++col)
            {
                if(play_board_data.get_del_board(Vector2i(row, col)) == false)
                {
                    start_game_window.draw(play_board_data.board[row][col]);
                }
            }
        }

        start_game_window.display();
    }
}


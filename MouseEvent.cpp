#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

bool check_mouse_clicked(Vector2i mouse_position, Vector2f object_position, Vector2f object_size)
{
    if(object_position.x < mouse_position.x && mouse_position.x < object_position.x + object_size.x)
    {
        if(object_position.y < mouse_position.y && mouse_position.y < object_position.y + object_size.y)
        {
            return true;
        }
    }
    return false;
}

string get_mouse_clicked()
{
    string click = "none";
    while(Mouse::isButtonPressed(Mouse::Left))
    {
        click = "left";
    }
    while(Mouse::isButtonPressed(Mouse::Right))
    {
        click = "right";
    }
    return click;
}

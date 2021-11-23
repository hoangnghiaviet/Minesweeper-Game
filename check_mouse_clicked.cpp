#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

// Ham tra ve true neu con tro chuot nam trong vung cua object, nguoc lai tra ve false
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

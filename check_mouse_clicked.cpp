#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

// Function will return true if mouse position is inside object area, otherwise return false
// mouse_position is mouse position
// object_position is coordinate of top-left conner of the object
// object_size if width and heigh of the object

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

#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

// Function return "left" if left mouse is clicked
// Function return "right" if right mouse is clicked
// Otherwise, function return "none"

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


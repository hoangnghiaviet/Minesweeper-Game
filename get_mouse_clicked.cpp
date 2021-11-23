#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

// Ham tra ve "left" neu click chuot trai, tra ve "right" neu click chuot phai
// Ham tra ve "none" neu khong co click nao xay ra
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


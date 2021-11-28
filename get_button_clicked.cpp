#include <vector>
#include <string>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

#include "MouseEvent.h"
#include "ButtonClass.h"

// Function will return -1 if no button is clicked
// Otherwise function will return the number corresponding to the button

int get_button_clicked(vector<ButtonClass> &button, int total_button, RenderWindow &window)
{
    string click = get_mouse_clicked();
    Vector2i mouse_position = Mouse::getPosition(window);
    for(int i = 0; i < total_button; ++i)
    {
        if(check_mouse_clicked(mouse_position, button[i].button.getPosition(), button[i].button.getSize()))
        {
            button[i].button.setFillColor(Color::Red);
            if(click == "left")
            {
                return i;
            }
        }
        else button[i].button.setFillColor(Color::White);
    }
    return -1;
}


#include "MouseEvent.h"

// Function will return true if mouse position is inside object area, otherwise return false
// mouse_position is mouse position
// object_position is coordinate of top-left conner of the object
// object_size if width and heigh of the object

bool check_mouse_clicked(sf::Vector2i mouse_position, sf::Vector2f object_position, sf::Vector2f object_size)
{
    if (object_position.x < mouse_position.x && mouse_position.x < object_position.x + object_size.x)
    {
        if (object_position.y < mouse_position.y && mouse_position.y < object_position.y + object_size.y)
        {
            return true;
        }
    }
    return false;
}

// Function return "left" if left mouse is clicked
// Function return "right" if right mouse is clicked
// Otherwise, function return "none"

std::string get_mouse_clicked()
{
    std::string click = "none";
    while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        click = "left";
    }
    while (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        click = "right";
    }
    return click;
}

// Function will return -1 if no button is clicked
// Otherwise function will return the number corresponding to the button

int get_button_clicked(std::vector<ButtonClass>& button, int total_button, sf::RenderWindow& window)
{
    std::string click = get_mouse_clicked();
    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
    for (int i = 0; i < total_button; ++i)
    {
        if (check_mouse_clicked(mouse_position, button[i].button.getPosition(), button[i].button.getSize()))
        {
            button[i].button.setFillColor(sf::Color::Red);
            if (click == "left")
            {
                return i;
            }
        }
        else button[i].button.setFillColor(sf::Color::White);
    }
    return -1;
}
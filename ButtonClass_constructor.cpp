#include <vector>
#include <string>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

#include "ButtonClass.h"

ButtonClass::ButtonClass(Vector2f _button_size, Vector2f _button_position)
{
    button.setSize(_button_size);
    button.setFillColor(Color::White);
    button.setPosition(_button_position);
}

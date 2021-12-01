#include "ButtonClass.h"

ButtonClass::ButtonClass(sf::Vector2f _button_size, sf::Vector2f _button_position, sf::Texture& _button_texture)
{
    button.setSize(_button_size);
    button.setFillColor(sf::Color::White);
    button.setPosition(_button_position);
    button.setTexture(&_button_texture);
}

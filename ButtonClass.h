#pragma once

#include <SFML/Graphics.hpp>

class ButtonClass {
public:
    ButtonClass() = default;
    ButtonClass(sf::Vector2f, sf::Vector2f, sf::Texture&);

    sf::RectangleShape button;
};

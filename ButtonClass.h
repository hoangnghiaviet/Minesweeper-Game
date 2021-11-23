#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class ButtonClass {
private:
public:
    RectangleShape button;

    ButtonClass() = default;

    ButtonClass(Vector2f _button_size, Vector2f _button_position);
};

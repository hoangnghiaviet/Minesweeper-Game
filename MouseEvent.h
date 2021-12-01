#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "ButtonClass.h"

bool check_mouse_clicked(sf::Vector2i, sf::Vector2f, sf::Vector2f);

std::string get_mouse_clicked();

int get_button_clicked(std::vector<ButtonClass>&, int, sf::RenderWindow&);

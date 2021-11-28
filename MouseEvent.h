#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

#include "ButtonClass.h"

bool check_mouse_clicked(Vector2i mouse_position, Vector2f object_position, Vector2f object_size);

string get_mouse_clicked();

int get_button_clicked(vector<ButtonClass> &button, int total_button, RenderWindow &window);

#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

bool check_mouse_clicked(Vector2i mouse_position, Vector2f object_position, Vector2f object_size);

string get_mouse_clicked();

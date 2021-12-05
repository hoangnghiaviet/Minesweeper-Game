#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "GameWindow.h"

void openSelectedWindow(int window_number);

void LoadGameWindow();

void NewGameWindow();

void InGameWindow(unsigned, unsigned, unsigned);

//void LeaderBoardWindow();

void InstructionWindow();

//void AuthorWindow();

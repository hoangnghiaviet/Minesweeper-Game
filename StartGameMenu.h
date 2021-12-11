#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "GameWindow.h"

void openSelectedWindow(int window_number);

void LoadGameWindow(unsigned, unsigned, unsigned, bool);

void NewGameWindow();

void LeaderBoardWindow();

void InstructionWindow();

void AuthorWindow();

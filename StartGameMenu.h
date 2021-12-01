#pragma once
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

#include "GameWindow.h"
#include "StartGameWindow.h"
#include "InGameWindow.h"
#include "ButtonClass.h"
#include "MouseEvent.h"

void openSelectedWindow(int window_number);

void LoadGameWindow();

void NewGameWindow();

//void LeaderBoardWindow();

void InstructionWindow();

//void AuthorWindow();

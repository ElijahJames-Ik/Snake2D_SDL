#pragma once
#include "SDL.h"
#include<string>

enum class GamePage { HOME, GAME, GAMEOVER };
class GlobalData
{
public:
	static SDL_Color white;
	static SDL_Color red;
	static int currentMenuSelection;
	static bool menuOptionChanged;
	static std::string menuItemTextFont;
	static std::string titleTextFont;
	static GamePage currentPage;

};
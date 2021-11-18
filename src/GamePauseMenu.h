#pragma once
#include<SDL.h>
#include<vector>
#include<memory>
#include "TextObject.h"

class GamePauseMenu
{
public:
	GamePauseMenu(int xPos, int yPos, int width, int height);
	void render();
	void update();


private:
	
	SDL_Rect menuBackgroundRect;
	std::vector<std::unique_ptr<TextObject>> menuTexts;
	SDL_Color white = { 255,255,255 };
	SDL_Color red = { 255,0,0 };
};
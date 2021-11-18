#pragma once
#include<SDL.h>
#include "TextObject.h"
#include<vector>
#include<memory>
class EnterNameBox
{
public:
	EnterNameBox(int xPos, int yPos, int width, int height);
	void render();
	void update();
	void init();


private:
	SDL_Rect inputBox;
	std::vector<std::unique_ptr<TextObject>> boxTexts;

	
};



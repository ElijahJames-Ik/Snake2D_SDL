#include "EnterNameBox.h"
#include "GlobalData.h"
#include "Game.h"
// create pause menu box
EnterNameBox::EnterNameBox(int xPos, int yPos, int width, int height)
{
	inputBox.x = xPos;
	inputBox.y = yPos;
	inputBox.w = width;
	inputBox.h = height;

	init();
	
}

void EnterNameBox::init()
{
	boxTexts.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 30, GlobalData::white, "Highscore Beat!", 310, 180));
	boxTexts.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Enter your name", 350, 225));
	boxTexts.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, GlobalData::enteredNameTextField.c_str(), 350, 250));
	boxTexts.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Must be 3 characters", 320, 300));
}

void EnterNameBox::render()
{
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(Game::renderer, &inputBox);
	

	for (auto itr = boxTexts.begin(); itr != boxTexts.end(); itr++)
	{
		(*itr)->render();
	}
}

void EnterNameBox::update()
{
	if (GlobalData::isInputTextToBeRedrawn)
	{
		(*(boxTexts.begin() + 2))->setText(GlobalData::enteredNameTextField.c_str());
		GlobalData::isInputTextToBeRedrawn = false;
	}
	
		
}
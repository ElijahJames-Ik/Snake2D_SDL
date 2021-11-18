#include "GamePauseMenu.h"
#include "GlobalData.h"
#include "Game.h"




// create pause menu box
GamePauseMenu::GamePauseMenu(int xPos, int yPos, int width, int height)
{
	menuBackgroundRect.x = xPos;
	menuBackgroundRect.y = yPos;
	menuBackgroundRect.w = width;
	menuBackgroundRect.h = height;

	menuTexts.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, red, "Resume Game", 350, 225));
	menuTexts.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, white, "Main Menu", 350, 255));
	menuTexts.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, white, "Exit", 350, 285));
}

void GamePauseMenu::render()
{
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(Game::renderer, &menuBackgroundRect);

	for (auto itr = menuTexts.begin(); itr != menuTexts.end(); itr++)
	{
		(*itr)->render();
	}
}

void GamePauseMenu::update()
{
	if (GlobalData::menuOptionChanged == true)
	{
		(*(menuTexts.begin()))->setColor(GlobalData::currentMenuSelection == 1 ? GlobalData::red : GlobalData::white);
		(*(menuTexts.begin() + 1))->setColor(GlobalData::currentMenuSelection == 2 ? GlobalData::red : GlobalData::white);
		(*(menuTexts.begin()+2))->setColor(GlobalData::currentMenuSelection == 3 ? GlobalData::red : GlobalData::white);
		
		GlobalData::menuOptionChanged = false;
	}
}
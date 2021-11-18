#include "GameOverPage.h"
#include "GlobalData.h"
#include <vector>
#include <memory>

#include "TextObject.h"



GameOverPage::GameOverPage(std::string score, GamePage pageType): Page(pageType)
{
	this->str = score;

}

// create gameover screen
void GameOverPage::initPage()
{
	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 50, GlobalData::white, "Game Over", 250, 170));
	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 30, GlobalData::white, str, 300, 280));
	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::red, "Play Again", 330, 340));
	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Main Menu", 330, 370));
	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Exit", 330, 400));
	isInitialized = true;
}

void GameOverPage::update()
{
	if (GlobalData::menuOptionChanged == true)
	{
		(*(pageText.begin() + 2))->setColor(GlobalData::currentMenuSelection == 1 ? GlobalData::red : GlobalData::white);
		(*(pageText.begin() + 3))->setColor(GlobalData::currentMenuSelection == 2 ? GlobalData::red : GlobalData::white);
		(*(pageText.begin() + 4))->setColor(GlobalData::currentMenuSelection == 3 ? GlobalData::red : GlobalData::white);
		GlobalData::menuOptionChanged = false;
	}
	
}

void GameOverPage::render()
{
	for (auto itr = pageText.begin(); itr != pageText.end(); itr++)
	{
		(*itr)->render();
	}
	
}

void GameOverPage::addedHighScore()
{
	SDL_StartTextInput();
}
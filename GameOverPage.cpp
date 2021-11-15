#include "GameOverPage.h"
#include "GlobalData.h"
#include <vector>
#include <memory>

#include "TextObject.h"



GameOverPage::GameOverPage(std::string score, GamePage pageType): Page(pageType)
{
	this->str = score;
}


void GameOverPage::initPage()
{
	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 50, GlobalData::white, "Game Over", 250, 170, 300, 100));
	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, str, 300, 280, 200, 50));
	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::red, "Play Again", 350, 340, 100, 25));
	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Main Menu", 350, 370, 100, 25));
	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Exit", 350, 400, 100, 25));
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
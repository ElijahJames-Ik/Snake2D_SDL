#include "GameOverPage.h"
#include "GlobalData.h"
#include <vector>
#include <memory>

#include "TextObject.h"

std::vector<std::unique_ptr<TextObject>> gameOverTexts;

GameOverPage::GameOverPage()
{

}

void GameOverPage::initData(const char* score)
{
	gameOverTexts.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 50, GlobalData::white, "Game Over", 250, 170, 300, 100));
	gameOverTexts.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, score, 300, 280, 200, 50));
	gameOverTexts.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::red, "1-Play Again", 350, 340, 100, 25));
	gameOverTexts.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "2-Main Menu", 350, 370, 100, 25));
	gameOverTexts.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "3-Exit", 350, 400, 100, 25));
}

void GameOverPage::update()
{
	if (GlobalData::menuOptionChanged == true)
	{
		(*(gameOverTexts.begin() + 2))->setColor(GlobalData::currentMenuSelection == 1 ? GlobalData::red : GlobalData::white);
		(*(gameOverTexts.begin() + 3))->setColor(GlobalData::currentMenuSelection == 2 ? GlobalData::red : GlobalData::white);
		(*(gameOverTexts.begin() + 4))->setColor(GlobalData::currentMenuSelection == 3 ? GlobalData::red : GlobalData::white);
		GlobalData::menuOptionChanged = false;
	}
}

void GameOverPage::render()
{
	for (auto itr = gameOverTexts.begin(); itr != gameOverTexts.end(); itr++)
	{
		(*itr)->render();
	}
}
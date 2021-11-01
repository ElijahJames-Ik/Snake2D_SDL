#include "MainMenuPage.h"
#include "GlobalData.h"
#include <iostream>



std::vector<std::unique_ptr<TextObject>> mainMenuTexts;


MainMenuPage::MainMenuPage()
{
}

void MainMenuPage::initData()
{
	//create texts for home page
	mainMenuTexts.clear();
	mainMenuTexts.emplace_back(std::make_unique<TextObject>(GlobalData::titleTextFont, 50, GlobalData::white, "Snake", 250, 170, 300, 100));
	mainMenuTexts.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::red, "1-New Game", 350, 270, 100, 25));
	mainMenuTexts.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "2-Options", 350, 300, 100, 25));
	mainMenuTexts.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "3-High Score", 350, 330, 100, 25));
	mainMenuTexts.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "4-Exit", 350, 360, 100, 25));
	GlobalData::menuOptionChanged = false;
}

MainMenuPage::~MainMenuPage()
{

}

void MainMenuPage::update()
{
	if (GlobalData::menuOptionChanged == true)
	{
		(*(mainMenuTexts.begin() + 1))->setColor(GlobalData::currentMenuSelection == 1 ? GlobalData::red : GlobalData::white);
		(*(mainMenuTexts.begin() + 2))->setColor(GlobalData::currentMenuSelection == 2 ? GlobalData::red : GlobalData::white);
		(*(mainMenuTexts.begin() + 3))->setColor(GlobalData::currentMenuSelection == 3 ? GlobalData::red : GlobalData::white);
		(*(mainMenuTexts.begin() + 4))->setColor(GlobalData::currentMenuSelection == 4 ? GlobalData::red : GlobalData::white);
		GlobalData::menuOptionChanged = false;
	}
}

void MainMenuPage::render()
{
	for (auto itr = mainMenuTexts.begin(); itr != mainMenuTexts.end(); itr++)
	{
		(*itr)->render();
	}	
}
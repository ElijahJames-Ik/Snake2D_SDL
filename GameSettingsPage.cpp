#include "GameSettingsPage.h"
#include "GlobalData.h"
#include <vector>
#include <memory>
#include <thread>





GameSettingsPage::GameSettingsPage(GamePage pageType): Page(pageType)
{
	
}

void GameSettingsPage::initPage()
{
	int height = 140;
	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 40, GlobalData::white, "Game Settings", 250, height, 300, 100));
	height += 120;

	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Map Settings", 320, height, 150, 30));

	height += 50;

	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Difficulty Settings", 320, height, 180, 30));
	height += 100;

	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Press enter to confirm selection", 200, height, 500, 30));
	height += 50;

	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Press escape to go back to the main menu.", 200, height, 500, 30));
	isInitialized = true;
}

void GameSettingsPage::update()
{
	if (GlobalData::menuOptionChanged == true)
	{
		(*(pageText.begin() + 1))->setColor(GlobalData::currentMenuSelection == 1 ? GlobalData::red : GlobalData::white);
		(*(pageText.begin() + 2))->setColor(GlobalData::currentMenuSelection == 2 ? GlobalData::red : GlobalData::white);
		
		GlobalData::menuOptionChanged = false;
	}
}

void GameSettingsPage::render()
{
	for (auto itr = pageText.begin(); itr != pageText.end(); itr++)
	{
		(*itr)->render();
	}
}
#include "SelectMapPage.h"
#include "GlobalData.h"
#include <vector>
#include <memory>
#include <thread>
#include <iostream>

std::vector<int> gameSettings;
std::thread loadHigscore;


SelectMapPage::SelectMapPage(GamePage pageType) : Page(pageType)
{
	
}

void SelectMapPage::initPage()
{
	gameSettings = provider.getGameData(GlobalData::gameSettingsFile, provider.gameData);
	int height = 140;
	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 50, GlobalData::white, "Select Map", 250, height, 300, 100));
	height += 120;
	
	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white,"1-Open Field", 350, height, 150, 30));

	height += 50;

	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "2-Boxed In", 350, height, 150, 30));
	height += 50;

	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Current Map: ", 280, height, 150, 30));
	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::green, gameSettings.front() == 0 ? "Open Field" : "Boxed In", 440, height, 150, 30));
	height += 100;
	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Press enter to confirm selection", 200, height, 500, 30));
	height += 50;
	
	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Press escape to go back to the main menu.", 200, height, 500, 30));
	isInitialized = true;

}

void SelectMapPage::update()
{
	if (GlobalData::menuOptionChanged == true)
	{
		(*(pageText.begin() + 1))->setColor(GlobalData::currentMenuSelection == 1 ? GlobalData::red : GlobalData::white);
		(*(pageText.begin() + 2))->setColor(GlobalData::currentMenuSelection == 2 ? GlobalData::red : GlobalData::white);

		GlobalData::menuOptionChanged = false;
	}
	if (GlobalData::settingsChanged == true)
	{
		
		std::cout << "Map Changed" << std::endl;
			std::string type = GlobalData::currentMenuSelection == 1 ? "0" : "1";
			std::string level = GlobalData::gameDifficulty == GameDifficult::EASY ? "0" : "1";
			provider.gameData = {
				"Map=" + type,
				"Difficult=" + level
			};
			provider.writeData(GlobalData::gameSettingsFile, provider.gameData);
			this->setItemText(GlobalData::currentMenuSelection == 1 ? "Open Field" : "Boxed In", 4, GlobalData::green);
			GlobalData::settingsChanged = false;
			GlobalData::isDataLoadRequired = true; 
		
	}
}

void SelectMapPage::render()
{
	for (auto itr = pageText.begin(); itr != pageText.end(); itr++)
	{
		(*itr)->render();
	}
}
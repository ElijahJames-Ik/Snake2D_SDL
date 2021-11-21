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

// create select map screen
void SelectMapPage::initPage()
{
	gameSettings = provider.getGameData(GlobalData::gameSettingsFile, provider.gameData);
	int height = 140;
	addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 50, GlobalData::white, "Select Map", 270, height));
	height += 120;
	
	addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white,"1-Open Field", 350, height));

	height += 50;

	addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "2-Boxed In", 350, height));
	height += 50;

	addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Current Map: ", 300, height));
	addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::green, gameSettings.front() == 0 ? "Open Field" : "Boxed In", 460, height));
	height += 100;
	addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Press enter to confirm selection.", 250, height));
	height += 50;
	
	addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Press escape to go back to the previous menu.", 180, height));
	setInitializationState(true);

}

void SelectMapPage::update()
{
	if (GlobalData::menuOptionChanged == true)
	{
		(*(getPageTextList().begin() + 1))->setColor(GlobalData::currentMenuSelection == 1 ? GlobalData::red : GlobalData::white);
		(*(getPageTextList().begin() + 2))->setColor(GlobalData::currentMenuSelection == 2 ? GlobalData::red : GlobalData::white);

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
			// update game settings file
			provider.writeData(GlobalData::gameSettingsFile, provider.gameData);
			this->setItemText(GlobalData::currentMenuSelection == 1 ? "Open Field" : "Boxed In", 4, GlobalData::green);
			GlobalData::settingsChanged = false;
			GlobalData::isDataLoadRequired = true; 
		
	}
}

void SelectMapPage::render()
{
	for (auto itr = getPageTextList().begin(); itr != getPageTextList().end(); itr++)
	{
		(*itr)->render();
	}
}
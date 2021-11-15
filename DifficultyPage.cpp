#include "DifficultyPage.h"
#include "GlobalData.h"
#include <vector>
#include <memory>
#include <thread>
#include <iostream>






DifficultyPage::DifficultyPage(GamePage pageType): Page(pageType)
{
	gameSettings = provider.getGameData(GlobalData::highscoreFile, provider.gameData);
}

// create difficult screen
void DifficultyPage::initPage()
{
	int height = 140;
	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 50, GlobalData::white, "Difficult Level", 250, height, 300, 100));
	height += 120;

	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Easy", 350, height, 150, 30));

	height += 50;

	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Normal", 350, height, 150, 30));
	height += 50;

	/*pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Hard", 350, height, 150, 30));
	height += 50;*/

	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Current Map: ", 280, height, 150, 30));
	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::green, gameSettings[1] == 0 ? "Easy" :  "Normal", 440, height, 150, 30));
	height += 100;

	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Press enter to confirm selection", 200, height, 500, 30));
	height += 50;

	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Press escape to go back to the main menu.", 200, height, 500, 30));
	
	isInitialized = true;

}

// update  difficult screen
void DifficultyPage::update()
{
	if (GlobalData::menuOptionChanged == true)
	{
		(*(pageText.begin() + 1))->setColor(GlobalData::currentMenuSelection == 1 ? GlobalData::red : GlobalData::white);
		(*(pageText.begin() + 2))->setColor(GlobalData::currentMenuSelection == 2 ? GlobalData::red : GlobalData::white);
		//(*(pageText.begin() + 3))->setColor(GlobalData::currentMenuSelection == 3 ? GlobalData::red : GlobalData::white);

		GlobalData::menuOptionChanged = false;
	}
	if (GlobalData::settingsChanged == true)
	{

		std::cout << "Difficult Changed" << std::endl;
		std::string level = std::to_string(GlobalData::currentMenuSelection - 1);
		std::string type = GlobalData::currentGameMap == MapType::OPEN_FIELD ? "0" : "1";
		provider.gameData = {
			"Map=" + type,
			"Difficult=" + level
		};
		provider.writeData(GlobalData::gameSettingsFile, provider.gameData);
		this->setItemText(GlobalData::currentMenuSelection == 1 ? "Easy" :  "Normal", 4, GlobalData::green);
		GlobalData::settingsChanged = false;
		GlobalData::isDataLoadRequired = true;

	}
}

// draw difficult screen
void DifficultyPage::render()
{
	for (auto itr = pageText.begin(); itr != pageText.end(); itr++)
	{
		(*itr)->render();
	}
}
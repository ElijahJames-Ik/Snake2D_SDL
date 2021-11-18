#include "MainMenuPage.h"
#include "GlobalData.h"
#include <iostream>






MainMenuPage::MainMenuPage(GamePage pageType) : Page(pageType)
{
}

// create home screen
void MainMenuPage::initPage()
{
	std::cout << "Creating page texts" << std::endl;
	std::cout << GlobalData::titleTextFont << std::endl;
	std::cout << GlobalData::menuItemTextFont << std::endl;
	//create texts for home page
	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::titleTextFont, 100, GlobalData::white, "Snake", 280, 170));
	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::red, "New Game", 330, 300));
	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Settings", 330, 330));
	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "High Score", 330, 360));
	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Exit", 330, 390));
	pageText.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Press enter to confirm selection.", 230, 450));
	std::cout << "Page content created" << std::endl;
	GlobalData::menuOptionChanged = false;
	isInitialized = true;
}

void MainMenuPage::loadGameData()
{
	DataProvider provider;
	auto data = provider.getGameData(GlobalData::gameSettingsFile, provider.gameData);
	GlobalData::currentGameMap = data[0] == 0 ? MapType::OPEN_FIELD : MapType::BOXED_IN;
	GlobalData::worldMapTexture = data[0] == 0 ? GlobalData::openFieldTexture : GlobalData::boxedInFieldTexture;
	GlobalData::tileMapFile = data[0] == 0 ? GlobalData::openFileMapFile : GlobalData::boxedInFileMapFile;
	GlobalData::gameDifficulty = data[1] == 0 ? GameDifficult::EASY : data[1] == 1 ? GameDifficult::NORMAL : GameDifficult::HARD;
	GlobalData::snakeSpeed = data[1] == 0 ? GlobalData::easySpeed : data[1] == 1 ? GlobalData::normalSpeed :GlobalData::hardSpeed;
}



void MainMenuPage::update()
{
	if (GlobalData::menuOptionChanged == true)
	{
		(*(pageText.begin() + 1))->setColor(GlobalData::currentMenuSelection == 1 ? GlobalData::red : GlobalData::white);
		(*(pageText.begin() + 2))->setColor(GlobalData::currentMenuSelection == 2 ? GlobalData::red : GlobalData::white);
		(*(pageText.begin() + 3))->setColor(GlobalData::currentMenuSelection == 3 ? GlobalData::red : GlobalData::white);
		(*(pageText.begin() + 4))->setColor(GlobalData::currentMenuSelection == 4 ? GlobalData::red : GlobalData::white);
		GlobalData::menuOptionChanged = false;
	}
	if (GlobalData::isDataLoadRequired)
	{
		loadGameData();
		GlobalData::isDataLoadRequired = false;
		GlobalData::isReLoadMapRequired = true;
	}
}

void MainMenuPage::render()
{
	for (auto itr = pageText.begin(); itr != pageText.end(); itr++)
	{
		(*itr)->render();
	}	
}
#include "MainMenuPage.h"
#include "GlobalData.h"
#include <iostream>






MainMenuPage::MainMenuPage(GamePage pageType) : Page(pageType)
{
}

MainMenuPage::~MainMenuPage()
{
	if (readGameFiles.joinable())
	{
		readGameFiles.join();
	}
}

// create home screen
void MainMenuPage::initPage()
{
	//create texts for home page
	addPageText(std::make_shared<TextObject>(GlobalData::titleTextFont, 100, GlobalData::white, "Snake", 280, 170));
	addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::red, "New Game", 330, 300));
	addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Settings", 330, 330));
	addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "High Score", 330, 360));
	addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Exit", 330, 390));
	addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Press enter to confirm selection.", 230, 450));
	GlobalData::menuOptionChanged = false;
	setInitializationState(true);
}

void MainMenuPage::loadGameData()
{
	DataProvider provider;
	auto data = provider.getGameData(GlobalData::gameSettingsFile, provider.gameData);
	GlobalData::currentGameMap = data[0] == 0 ? MapType::OPEN_FIELD : MapType::BOXED_IN;
	GlobalData::worldMapTexture = data[0] == 0 ? GlobalData::openFieldTexture : GlobalData::boxedInFieldTexture;
	GlobalData::tileMapFile = data[0] == 0 ? GlobalData::openFileMapFile : GlobalData::boxedInFileMapFile;
	GlobalData::gameDifficulty = data[1] == 0 ? GameDifficult::EASY : GameDifficult::NORMAL;
	GlobalData::snakeSpeed = data[1] == 0 ? GlobalData::easySpeed : GlobalData::normalSpeed ;
}



void MainMenuPage::update()
{
	if (GlobalData::menuOptionChanged == true)
	{
		(*(getPageTextList().begin() + 1))->setColor(GlobalData::currentMenuSelection == 1 ? GlobalData::red : GlobalData::white);
		(*(getPageTextList().begin() + 2))->setColor(GlobalData::currentMenuSelection == 2 ? GlobalData::red : GlobalData::white);
		(*(getPageTextList().begin() + 3))->setColor(GlobalData::currentMenuSelection == 3 ? GlobalData::red : GlobalData::white);
		(*(getPageTextList().begin() + 4))->setColor(GlobalData::currentMenuSelection == 4 ? GlobalData::red : GlobalData::white);
		GlobalData::menuOptionChanged = false;
	}
	if (GlobalData::isDataLoadRequired)
	{
		readGameFiles = std::thread([this]() {

			loadGameData();
		});
	
		GlobalData::isDataLoadRequired = false;
		GlobalData::isReLoadMapRequired = true;
		readGameFiles.join();
	}
	
}

void MainMenuPage::render()
{
	for (auto itr = getPageTextList().begin(); itr != getPageTextList().end(); itr++)
	{
		(*itr)->render();
	}	
}
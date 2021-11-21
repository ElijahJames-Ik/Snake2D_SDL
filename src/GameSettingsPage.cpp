#include "GameSettingsPage.h"
#include "GlobalData.h"
#include <vector>
#include <memory>
#include <thread>





GameSettingsPage::GameSettingsPage(GamePage pageType): Page(pageType)
{
	
}
// creae game settings screen
void GameSettingsPage::initPage()
{
	int height = 140;
	addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 40, GlobalData::white, "Game Settings", 270, height));
	height += 120;

	addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Map Settings", 320, height));

	height += 50;

	addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Difficulty Settings", 320, height));
	height += 100;

	addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Press enter to confirm selection", 250, height));
	height += 50;

	addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Press escape to go back to the main menu.", 200, height));
	setInitializationState(true);
}

void GameSettingsPage::update()
{
	if (GlobalData::menuOptionChanged == true)
	{
		(*(getPageTextList().begin() + 1))->setColor(GlobalData::currentMenuSelection == 1 ? GlobalData::red : GlobalData::white);
		(*(getPageTextList().begin() + 2))->setColor(GlobalData::currentMenuSelection == 2 ? GlobalData::red : GlobalData::white);
		
		GlobalData::menuOptionChanged = false;
	}
}

void GameSettingsPage::render()
{
	for (auto itr = getPageTextList().begin(); itr != getPageTextList().end(); itr++)
	{
		(*itr)->render();
	}
}
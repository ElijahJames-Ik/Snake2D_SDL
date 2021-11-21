#include "GameOverPage.h"
#include "GlobalData.h"
#include <vector>
#include <memory>

#include "TextObject.h"



GameOverPage::GameOverPage(std::string score, GamePage pageType): Page(pageType)
{
	this->setDynamicTextValue(score);

}

// create gameover screen
void GameOverPage::initPage()
{
	addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 50, GlobalData::white, "Game Over", 250, 170));
	addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 30, GlobalData::white, getDynamicTextValue(), 300, 280));
	addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::red, "Play Again", 330, 340));
	addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Main Menu", 330, 370));
	addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Exit", 330, 400));
	setInitializationState(true);
}

void GameOverPage::update()
{
	if (GlobalData::menuOptionChanged == true)
	{
		(*(getPageTextList().begin() + 2))->setColor(GlobalData::currentMenuSelection == 1 ? GlobalData::red : GlobalData::white);
		(*(getPageTextList().begin() + 3))->setColor(GlobalData::currentMenuSelection == 2 ? GlobalData::red : GlobalData::white);
		(*(getPageTextList().begin() + 4))->setColor(GlobalData::currentMenuSelection == 3 ? GlobalData::red : GlobalData::white);
		GlobalData::menuOptionChanged = false;
	}
	
}

void GameOverPage::render()
{
	for (auto itr = getPageTextList().begin(); itr != getPageTextList().end(); itr++)
	{
		(*itr)->render();
	}
	
}

void GameOverPage::addedHighScore()
{
	SDL_StartTextInput();
}
#include "HighscorePage.h"
#include "GlobalData.h"
#include <vector>
#include <memory>
#include <thread>
#include <iostream>





HighscorePage::HighscorePage(GamePage pageType): Page(pageType)
{
	loadScores();
}

// create highscore page
void HighscorePage::initPage()
{
	
	int height = 140;
	addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 50, GlobalData::white, "Highscores", 250, height));
	height += 80;
	for (int i = 0; i < highscores.size(); i++)
	{
		height += 40;
		addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, highscores[i], 350, height));
	}
	height += 80; highscores = provider.getHighscoresAsListOfStrings(GlobalData::highscoreFile);
	addPageText(std::make_shared<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Press escape to go back to the main menu.", 200, height));
	setInitializationState(true);
}

void HighscorePage::loadScores()
{
	highscores = provider.getHighscoresAsListOfStrings(GlobalData::highscoreFile);
}

void HighscorePage::update()
{
	
}

void HighscorePage::render()
{
	for (auto itr = getPageTextList().begin(); itr != getPageTextList().end(); itr++)
	{
		(*itr)->render();
	}
}
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
	highScoreTexts.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 50, GlobalData::white, "Highscores", 250, height));
	height += 80;
	for (int i = 0; i < highscore.size(); i++)
	{
		height += 40;
		highScoreTexts.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, highscore[i], 350, height));
	}
	height += 80; highscore = provider.getHighscoresAsListOfStrings(GlobalData::highscoreFile);
	highScoreTexts.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Press escape to go back to the main menu.", 200, height));
	isInitialized = true;
}

void HighscorePage::loadScores()
{
	highscore = provider.getHighscoresAsListOfStrings(GlobalData::highscoreFile);
}

void HighscorePage::update()
{
	
}

void HighscorePage::render()
{
	for (auto itr = highScoreTexts.begin(); itr != highScoreTexts.end(); itr++)
	{
		(*itr)->render();
	}
}
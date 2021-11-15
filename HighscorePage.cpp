#include "HighscorePage.h"
#include "GlobalData.h"
#include <vector>
#include <memory>
#include <thread>

std::vector<std::unique_ptr<TextObject>> highScoreTexts;
std::vector<int> highscore;



HighscorePage::HighscorePage(GamePage pageType): Page(pageType)
{
	highscore = provider.getGameData(GlobalData::highscoreFile, provider.highscoreData);
}

// create highscore page
void HighscorePage::initPage()
{
	int height = 140;
	highScoreTexts.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 50, GlobalData::white, "Game Options", 250, height, 300, 100));
	height += 80;
	for (int i = 0; i < highscore.size(); i++)
	{
		height += 40;
		highScoreTexts.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, std::to_string(highscore[i]), 350, height, 80, 20));
	}
	height += 80;
	highScoreTexts.emplace_back(std::make_unique<TextObject>(GlobalData::menuItemTextFont, 20, GlobalData::white, "Press escape to go back to the main menu.", 200, height, 500, 30));
	isInitialized = true;
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
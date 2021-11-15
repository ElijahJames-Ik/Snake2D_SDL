#include "Page.h"



Page::Page(GamePage pageType)
{
	this->pageType = pageType;
	this->isInitialized = false;
}

void Page::setItemText(std::string str, int itemIndex, SDL_Color color)
{
	this->str = str;
	int xPos = pageText[itemIndex]->xPos;
	int yPos = pageText[itemIndex]->yPos;
	int height = pageText[itemIndex]->height;
	int width = pageText[itemIndex]->width;
	int fontSize = pageText[itemIndex]->fontSize;


	pageText[itemIndex] = std::make_unique<TextObject>(GlobalData::menuItemTextFont, fontSize, color, str, xPos, yPos, width, height);
}
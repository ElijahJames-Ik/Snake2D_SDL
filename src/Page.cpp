#include "Page.h"



Page::Page(GamePage pageType): pageType(pageType)
{
	this->isInitialized = false;
}
// change text on screen
void Page::setItemText(std::string str, int itemIndex, SDL_Color color)
{
	setDynamicTextValue(str);
	int xPos = pageTexts[itemIndex]->getXPos();
	int yPos = pageTexts[itemIndex]->getYPos();
	int fontSize = pageTexts[itemIndex]->getFontSize();


	pageTexts[itemIndex] = std::make_shared<TextObject>(GlobalData::menuItemTextFont, fontSize, color, str, xPos, yPos);
}

GamePage Page::getPageType()
{
	return pageType;
}
bool Page::getInitializationState()
{
	return isInitialized;
}

void  Page::setInitializationState(bool state)
{
	isInitialized = state;
}
std::vector<std::shared_ptr<TextObject>> &Page::getPageTextList()
{
	return pageTexts;
}
void Page::addPageText(std::shared_ptr<TextObject> textObject)
{
	pageTexts.emplace_back(textObject);
}
void  Page::setDynamicTextValue(std::string value)
{
	dynamicTextValue = value;
}

std::string Page::getDynamicTextValue()
{
	return dynamicTextValue;
}
#pragma once
#include "GlobalData.h"
#include <vector>
#include <memory>
#include "TextObject.h"
#include "DataProvider.h"
#include <string>

class Page
{
public:
	Page(GamePage pageType);
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void initPage() = 0;
	void setItemText(std::string str, int itemIndex, SDL_Color color);
	GamePage getPageType();
	bool getInitializationState();
	void setInitializationState(bool state);
	std::vector<std::shared_ptr<TextObject>> &getPageTextList();
	void addPageText(std::shared_ptr<TextObject> textObject);
	void setDynamicTextValue(std::string value);
	std::string getDynamicTextValue();
	
private:
	GamePage pageType;
	bool isInitialized;
	std::string dynamicTextValue;
	std::vector<std::shared_ptr<TextObject>> pageTexts;
};


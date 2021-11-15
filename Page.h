#pragma once
#include "GlobalData.h"
#include <vector>
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
	GamePage pageType;
	bool isInitialized;
	std::string str;
	std::vector<std::unique_ptr<TextObject>> pageText;
};


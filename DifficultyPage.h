#pragma once
#include "Page.h"
#include "DataProvider.h"
#include "TextObject.h"
class DifficultyPage : public Page
{
public:
	DifficultyPage(GamePage pageType);
	virtual void update()override;
	virtual void render()override;
	virtual void initPage()override;

private:
	DataProvider provider;
	std::vector<int> gameSettings;
};


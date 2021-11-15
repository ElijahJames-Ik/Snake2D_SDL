#pragma once
#include<vector>
#include<memory>
#include "TextObject.h"
#include "Page.h"

class MainMenuPage : public Page
{
public:
	MainMenuPage(GamePage pageType);
	void render() override;
	void update() override;
	void initPage() override;
	void loadGameData();
	
};
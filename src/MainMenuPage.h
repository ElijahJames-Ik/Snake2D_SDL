#pragma once
#include<vector>
#include<memory>
#include<thread>
#include "TextObject.h"
#include "Page.h"

class MainMenuPage : public Page
{
public:
	MainMenuPage(GamePage pageType);
	~MainMenuPage();
	void render() override;
	void update() override;
	void initPage() override;
	void loadGameData();
private:
	std::thread readGameFiles;
	
};
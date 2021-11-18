#pragma once
#include "Page.h"
#include "EnterNameBox.h"
#include <string>
#include <memory>

class GameOverPage : public Page
{
public:
	GameOverPage(std::string score, GamePage pageType);
	void update() override;
	void render() override;
	void initPage() override;
	void addedHighScore();
	
};
#pragma once
#include "Page.h"
#include <string>

class GameOverPage : public Page
{
public:
	GameOverPage(std::string score, GamePage pageType);
	void update() override;
	void render() override;
	void initPage() override;

};
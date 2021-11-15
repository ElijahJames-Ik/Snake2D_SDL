#pragma once

#include "GlobalData.h"
#include <vector>
#include "TextObject.h"
#include "Page.h"
class GameSettingsPage : public Page
{
public:
	GameSettingsPage(GamePage pageType);
	void update()override;
	void render()override;
	void initPage()override;



};
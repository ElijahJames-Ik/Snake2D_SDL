#pragma once
#include "GlobalData.h"
#include "Page.h"
#include <vector>
#include "TextObject.h"
#include "DataProvider.h"


class SelectMapPage : public Page
{
public:
	SelectMapPage(GamePage pageType);
	void update()override;
	void render()override;
	void initPage()override;
private:
	DataProvider provider;
};




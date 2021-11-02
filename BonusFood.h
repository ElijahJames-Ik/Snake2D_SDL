#pragma once

#include <memory>
#include "SnakeFood.h"
class BonusFood : public SnakeFood
{
public:
	BonusFood(const char* textureSheet, int x, int y, int width, int height);
	void update() override;
	void render() override;
	bool isBonusShowing = false;
};
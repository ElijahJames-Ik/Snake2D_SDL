#pragma once


#include "Actor.h"

class SnakeFood : public Actor
{
public:
	SnakeFood(const char* textureSheet, int x, int y, int width, int height);
	~SnakeFood();
	void update() override;
	void render() override;
	bool isFoodEaten = true;
};
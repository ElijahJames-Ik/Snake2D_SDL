#pragma once
#include "SnakeFood.h"


class FoodManager
{
public:
	FoodManager(int width, int height);
	void generateFood();
	void update();
	void render();

private:
	std::unique_ptr<SnakeFood> food;
	int width;
	int height;

};
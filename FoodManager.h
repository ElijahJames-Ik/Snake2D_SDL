#pragma once
#include "SnakeFood.h"
#include "Snake.h"


class FoodManager
{
public:
	FoodManager(int width, int height, std::shared_ptr<Snake> snake);
	void generateFood();
	void update();
	void render();

private:
	std::unique_ptr<SnakeFood> food;
	std::shared_ptr<Snake> snake;
	int width;
	int height;

};
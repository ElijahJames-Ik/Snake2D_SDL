#pragma once
#include "SnakeFood.h"
#include "Snake.h"
#include "BonusFood.h"
#include <thread>
#include <chrono>


class FoodManager
{
public:
	FoodManager(int width, int height, std::shared_ptr<Snake> snake);
	~FoodManager();
	void generateFood();
	void generateBonus();
	void update();
	void render();

private:
	void generate(std::unique_ptr<SnakeFood>& foodPtr, int foodWidth, int foodHeight);
	std::unique_ptr<SnakeFood> food;
	std::unique_ptr<SnakeFood> bonus;
	std::shared_ptr<Snake> snake;
	int width;
	int height;
	// number of normal food to be eaten before bonus appears
	int bonusReqCount = 5;

	int currentCount = 0;
	bool isBonusVisible = false;
	std::thread timerThread;
	

};
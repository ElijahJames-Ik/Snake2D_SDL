#pragma once
#include "Game.h"
#include "Snake.h"


class Controller
{
public:
	Controller(std::shared_ptr<Snake> snake);
	void update();
	
private:
	std::shared_ptr<Snake> snakePtr;
};
#pragma once

#include "Snake.h"


class Controller
{
public:
	Controller(std::shared_ptr<Snake> snakePtr);
	void captureInput();
	
private:
	std::shared_ptr<Snake> snakePtr;
};
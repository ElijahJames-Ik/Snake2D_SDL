#pragma once

#include "Snake.h"


class Controller
{
public:
	Controller(std::shared_ptr<Snake> snakePtr);
	~Controller();
	void captureInput();
private:
	std::shared_ptr<Snake> snakePtr;
	const Uint8* keyBoardState = SDL_GetKeyboardState(NULL);
	void up();
	void down();
	void right();
	void left();
	
};
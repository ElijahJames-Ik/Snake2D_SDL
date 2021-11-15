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
	void moveSnake(const char* texture, int x, int y, const char* directionStr, Direction direction);
	void menuNavigation(int menuItems);
	void homeEnterOperation();
	void gameOverEnterOperation();
	void highscoreEscapeOperation();
	void settingsEnterOperation();
	void settingsEscapeOperation();
	void changeSettingsEnterOperation();
	void changeSettingsEscapeOperation();
	void difficultyEscapeOperation();
	void snakeNavigation();
	void snakePausedMenuEnterOperation();
	Vector2D snakeHeadLocation;
	bool isMovementLocked = false;

	
};
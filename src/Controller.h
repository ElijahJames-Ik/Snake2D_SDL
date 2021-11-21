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
	// change snake direction to up
	void up();
	// change snake direction to down
	void down();
	// change snake direction to right
	void right();
	// change snake direction to left
	void left();
	// handles menu navigation for all pages that contain menus
	void menuNavigation(int menuItems);
	// holds code to be executed in the home page when the enter key is pressed
	void homeEnterOperation();
	// holds code to be executed in the game over page when the enter key is pressed
	void gameOverEnterOperation();
	// holds code to be executed in the highscore page when the escape key is pressed
	void highscoreEscapeOperation();
	// holds code to be executed in the settings page when the enter key is pressed
	void settingsEnterOperation();
	// holds code to be executed in the settings page when the escape key is pressed
	void settingsEscapeOperation();
	// holds code to be executed in the map settings page when the enter key is pressed
	void changeSettingsEnterOperation();
	// holds code to be executed in the map settings page when the escape key is pressed
	void changeSettingsEscapeOperation();
	// holds code to be executed in the difficulty page when the escape key is pressed
	void difficultyEscapeOperation();
	// handles snake navigation
	void snakeNavigation();
	// holds code to be executed in the game page when the snake is paused and the enter key is pressed
	void snakePausedMenuEnterOperation();
	// holds code to for saving new highscore
	void saveHighScoreOperation();
	// holds code for handling edit text object for input user name when he/she beats any highscore
	void handleEditBoxInput();
	Vector2D snakeHeadLocation;

	
};
#pragma once


#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include "MainMenuPage.h"
#include "GameOverPage.h"
#include "HighscorePage.h"
#include "GameSettingsPage.h"
#include "SelectMapPage.h"
#include "DifficultyPage.h"


class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xPos, int yPos, int width, int height);
	void handleEvents();
	void update();
	void render();
	void updateWindowTitle();
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool isGameRunning;
	static int windowWidth;
	static int windowHeight;
private:
	SDL_Window* gameWindow;
	/*std::unique_ptr<MainMenuPage> mainPagePtr;
	std::unique_ptr<GameOverPage> gameOverPagePtr;
	std::unique_ptr<HighscorePage> highScorePagePtr;
	std::unique_ptr<GameSettingsPage> gameSettingsPagePtr;
	std::unique_ptr<SelectMapPage> selectMapPagePtr;
	std::unique_ptr<DifficultyPage> difficultyPagePtr;*/
	
	std::vector<std::unique_ptr<Page>> pages;

	
};
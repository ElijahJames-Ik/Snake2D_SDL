#include "Game.h"
#include "GlobalData.h"
#include "Snake.h"
#include "FoodManager.h"
#include "WorldMap.h"
#include "TextObject.h"
#include <string>
#include <thread>
#include <future>
#include "Controller.h"
#include "GamePauseMenu.h"




const char* tileMapFile = "assets/defaultMap.txt";
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::isGameRunning = false;
bool scoreDisplayed = false;
std::shared_ptr<Snake> snake = nullptr;
std::unique_ptr<Controller> controller = nullptr;
std::unique_ptr<FoodManager> food;
std::unique_ptr<WorldMap> background = nullptr;
std::unique_ptr<GamePauseMenu> pausedMenu = nullptr;






int Game::windowWidth = 800;
int Game::windowHeight = 640;

SDL_Color white = { 255,255,255 };
SDL_Color red = { 255,0,0 };




Game::Game()
{
	food = nullptr;
	gameOverPagePtr = nullptr;
	mainPagePtr = nullptr;
}

Game::~Game()
{
	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(renderer);
}


void showPauseMenu()
{

}




void Game::init(const char* title, int xPos, int yPos, int width, int height)
{
	
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		gameWindow = SDL_CreateWindow(title, xPos, yPos, width, height, SDL_WINDOW_SHOWN);
		if (gameWindow)
		{
			std::cout << "Game window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(gameWindow, -1, 0);

		if (renderer)
		{
			std::cout << "Game renderer created" << std::endl;
		}

		isGameRunning = true;

		snake = std::make_shared<Snake>(5);
		food = std::make_unique<FoodManager>(Game::windowWidth, Game::windowHeight, snake);
		
		std::cout << "Snake created" << std::endl;
		background = std::make_unique<WorldMap>();
		background->LoadWorldMap(tileMapFile, 25, 20);
		controller = std::make_unique<Controller>(snake);
		mainPagePtr = std::unique_ptr<MainMenuPage>();
		mainPagePtr->initData();
	}
	else
	{
		std::cout << "SDL Initialization failed" << std::endl;
	}
	
}
void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isGameRunning = false;
		break;
	default:
		break;
	}
}
void Game::update()
{
	// capture keyboard input
	controller->captureInput();
	if (GlobalData::currentPage == GamePage::GAME)
	{
		if (!snake->isSnakeDead)
		{
			snake->update();
			food->update();
		}
		if (snake->isGamePaused == true)
		{
			
			if (pausedMenu == nullptr)
			{
				pausedMenu = std::make_unique<GamePauseMenu>(300, 170, 200, 200);
			}
			else
			{
				pausedMenu->update();
			}
			
			
		}
		
	}
	else if (GlobalData::currentPage == GamePage::HOME)
	{
		//Update main menu page
		if (mainPagePtr != nullptr)
		{
			mainPagePtr->update();
		}
		else
		{
			mainPagePtr = std::make_unique<MainMenuPage>();
			mainPagePtr->initData();
		}
	}
	else if (GlobalData::currentPage == GamePage::GAMEOVER)
	{
		
		if (gameOverPagePtr != nullptr)
		{
			gameOverPagePtr->update();
		}
		else
		{
			std::string score = "Your Score: " + std::to_string(snake->getScore());
			gameOverPagePtr = std::make_unique<GameOverPage>();
			gameOverPagePtr->initData(score.c_str());
		}
		
	}
}



void Game::render()
{
	
	SDL_RenderClear(renderer);
	if (GlobalData::currentPage == GamePage::GAME)
	{
		if (!snake->isSnakeDead)
		{
			background->render();
			snake->render();
			food->render();
			if (snake->isGamePaused == true && pausedMenu != nullptr)
			{
				pausedMenu->render();
			}

		}
	}
	else if (GlobalData::currentPage == GamePage::GAMEOVER)
	{
		if (gameOverPagePtr != nullptr)
		{
			gameOverPagePtr->render();
		}
	}
	else if (GlobalData::currentPage == GamePage::HOME)
	{
		if (mainPagePtr != nullptr)
		{
			mainPagePtr->render();
		}
		
	}
	
	SDL_RenderPresent(renderer);
}



#include "Game.h"
#include "Snake.h"
#include "FoodManager.h"
#include "WorldMap.h"




const char* tileMapFile = "assets/defaultMap.txt";
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::isGameRunning = false;
std::shared_ptr<Snake> snake = nullptr;
std::unique_ptr<FoodManager> food;
std::unique_ptr<WorldMap> background = nullptr;


int Game::windowWidth = 800;
int Game::windowHeight = 640;




Game::Game()
{
	food = nullptr;
}

Game::~Game()
{
	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(renderer);
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
		snake->createSnake();
		food = std::make_unique<FoodManager>(Game::windowWidth, Game::windowHeight, snake);
		
		std::cout << "Snake created" << std::endl;
		background = std::make_unique<WorldMap>();
		background->LoadWorldMap(tileMapFile, 25, 20);
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
	snake->update();
	food->update();
	

}
void Game::render()
{
	
	SDL_RenderClear(renderer);
	if (!snake->isSnakeDead)
	{
		background->render();
		snake->render();
		food->render();
	}
	
	SDL_RenderPresent(renderer);
}



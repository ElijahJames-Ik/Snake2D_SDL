#include "Game.h"
#include "Snake.h"




SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::isGameRunning = false;
std::shared_ptr<Snake> snake = nullptr;




Game::Game()
{

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
		
		

		std::cout << "Snake created" << std::endl;
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
	
	
}
void Game::render()
{
	SDL_RenderClear(renderer);
	snake->render();
	 SDL_RenderPresent(renderer);
}



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
#include "Collision.h"
#include "DataProvider.h"





SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::isGameRunning = false;
bool scoreDisplayed = false;
std::shared_ptr<Snake> snake = nullptr;
std::unique_ptr<Controller> controller = nullptr;
std::unique_ptr<FoodManager> food;
std::unique_ptr<WorldMap> background = nullptr;
std::unique_ptr<GamePauseMenu> pausedMenu = nullptr;

std::vector<int> gameData;
std::thread readGameFiles;



int Game::windowWidth = 800;
int Game::windowHeight = 640;

SDL_Color white = { 255,255,255 };
SDL_Color red = { 255,0,0 };




Game::Game()
{
	food = nullptr;
	pages.emplace_back(std::make_unique<MainMenuPage>(GamePage::HOME));
	pages.emplace_back(std::make_unique<GameOverPage>("Your Score: 0", GamePage::GAMEOVER));
	pages.emplace_back(std::make_unique<HighscorePage>(GamePage::HIGHSCORE));
	pages.emplace_back(std::make_unique<GameSettingsPage>(GamePage::SETTINGS));
	pages.emplace_back(std::make_unique<SelectMapPage>(GamePage::MAPSETTINGS));
	pages.emplace_back(std::make_unique<DifficultyPage>(GamePage::DIFFICULT));
	
}

Game::~Game()
{
	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
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

		readGameFiles = std::thread([this]() {

			DataProvider provider;
			gameData = provider.getGameData(GlobalData::gameSettingsFile, provider.gameData);	
		});

		snake = std::make_shared<Snake>(5);
		food = std::make_unique<FoodManager>(Game::windowWidth, Game::windowHeight, snake);
		std::cout << "Snake created" << std::endl;
		background = std::make_unique<WorldMap>();
		readGameFiles.join();

		// load game data
		/*if (gameData[0] == 0)
		{
			GlobalData::currentGameMap = MapType::OPEN_FIELD;
			GlobalData::worldMapTexture = GlobalData::openFieldTexture;
			GlobalData::tileMapFile = GlobalData::openFileMapFile;
		}
		else
		{
			GlobalData::currentGameMap = MapType::BOXED_IN;
			GlobalData::worldMapTexture = GlobalData::boxedInFieldTexture;
			GlobalData::tileMapFile = GlobalData::boxedInFileMapFile;
		}*/
		
		controller = std::make_unique<Controller>(snake);
		pages.front()->initPage();
				
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
			if (GlobalData::currentGameMap == MapType::BOXED_IN)
			{
				if (background->collisionBoxes.size() > 0 && !snake->isSnakeDead)
				{
					for (auto itr = background->collisionBoxes.begin(); itr != background->collisionBoxes.end(); itr++)
					{
						if (Collision::AABB(snake->snakeBody.front()->destRect, (*itr)->destRect) == true)
						{
							std::cout << "Snake is dead" << std::endl;
							std::cout << (*itr)->destRect.x << std::endl;
							snake->snakeBody.front()->velocity.x = 0;
							snake->snakeBody.front()->velocity.y = 0;
							snake->isSnakeDead = true;
							GlobalData::currentPage = GamePage::GAMEOVER;
							GlobalData::currentMenuSelection = 1;
						}
					}
				}

			}
			
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

	for (auto itr = pages.begin(); itr != pages.end(); itr++)
	{
		if ((*itr)->pageType == GlobalData::currentPage)
		{
			if ((*itr)->isInitialized)
			{
				(*itr)->update();
				if ((*itr)->pageType == GamePage::GAMEOVER)
				{
					std::string score = "Your Score: " + std::to_string(snake->getScore());
					((*itr))->setItemText(score, 1, GlobalData::white);
				}
				else if ((*itr)->pageType == GamePage::HOME)
				{
					if (GlobalData::isDataLoadRequired)
					{
						auto tmpPtr = static_cast<MainMenuPage*>((*itr).get());
						tmpPtr->loadGameData();
						GlobalData::isDataLoadRequired = false;
						std::cout << "Data Loaded" << std::endl;
						background->collisionBoxes.clear();
						background->LoadWorldMap(GlobalData::tileMapFile, 25, 20);
					}
				}
				
			}
			else
			{
				(*itr)->initPage();
				if ((*itr)->pageType == GamePage::GAMEOVER)
				{
				
					std::string score = "Your Score: " + std::to_string(snake->getScore());
					((*itr))->setItemText(score, 1, GlobalData::white);
				}
			}
			break;
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

	for (auto itr = pages.begin(); itr != pages.end(); itr++)
	{
		if ((*itr)->pageType == GlobalData::currentPage)
		{
			if ((*itr)->isInitialized)
			{
				(*itr)->render();
				break;
			}
		}
	}
	
	SDL_RenderPresent(renderer);
}



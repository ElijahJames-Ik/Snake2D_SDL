#include "Game.h"
#include "GlobalData.h"
#include "Snake.h"
#include "FoodManager.h"
#include "WorldMap.h"
#include "TextObject.h"
#include <string>
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
	
	if (loadMapData.joinable())
	{
		loadMapData.join();
	}
	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}


void Game::updateWindowTitle()
{
	SDL_SetWindowTitle(gameWindow, GlobalData::windowTitle.c_str());
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
		// read game settings from file
		
		// create snake of length 5
		snake = std::make_shared<Snake>(5);
		food = std::make_unique<FoodManager>(Game::windowWidth, Game::windowHeight, snake);
		std::cout << "Snake created" << std::endl;
		// create background map
		background = std::make_unique<WorldMap>();
		
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

	controller->captureInput();
	
}
void Game::update()
{
	// capture keyboard input
	if (snake->getTitleUpdateState())
	{
		updateWindowTitle();
		snake->setTitleUpdateState(false);
	}
	if (GlobalData::isFoodManagerResetRequired)
	{
		food->resetManager();
		GlobalData::isFoodManagerResetRequired = false;
	}

	
	if (GlobalData::currentPage == GamePage::GAME)
	{
		if (!snake->getSnakeState())
		{
			snake->update();
			food->update();
			// check if snake head collides with the map if it's boxed in map is choose as the game map
			snake->checkIfSnakeCollidiesWithBoxedInMap(background);
			
		}
	
		if (snake->getHighScoreBeatState())
		{
			if (newHighscoreBox == nullptr)
			{
				newHighscoreBox = std::make_unique<EnterNameBox>(290, 170, 290, 250);
			}
			else
			{
				newHighscoreBox->update();
			}
			
		}
		if (GlobalData::isGameOver)
		{
			GlobalData::windowTitle = "SNAKE";
			updateWindowTitle();
			GlobalData::isGameOver = false;
		}
			
			
			
		
		if (snake->getGamePausedState())
		{
			if (pausedMenu == nullptr)
			{
				pausedMenu = std::make_unique<GamePauseMenu>(300, 170, 250, 250);
			}
			else
			{
				pausedMenu->update();
			}	
		}
		
		
	}

	for (auto itr = pages.begin(); itr != pages.end(); itr++)
	{
		// update current screen
		if ((*itr)->getPageType() == GlobalData::currentPage)
		{
			if ((*itr)->getInitializationState())
			{
				(*itr)->update();
				if ((*itr)->getPageType() == GamePage::GAMEOVER)
				{
					std::string score = "Your Score: " + std::to_string(snake->getScore());
					((*itr))->setItemText(score, 1, GlobalData::white);
				}
				else if ((*itr)->getPageType() == GamePage::HIGHSCORE)
				{
					if (GlobalData::isHighscoreLoadRequired)
					{
						(*itr) = std::make_unique<HighscorePage>(GamePage::HIGHSCORE);
						GlobalData::isHighscoreLoadRequired = false;
					}
				}
				else if ((*itr)->getPageType() == GamePage::HOME)
				{
					
					//Load game data
					if (GlobalData::isReLoadMapRequired)
					{
						
						loadMapData = std::thread([this]() {
							background->LoadWorldMap(GlobalData::tileMapFile, 25, 20);
						});
						
						
						GlobalData::isReLoadMapRequired = false;
						loadMapData.join();
					}
				}
				
			}
			else
			{
				(*itr)->initPage();
				if ((*itr)->getPageType() == GamePage::GAMEOVER)
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
		if (!snake->getSnakeState() || snake->getHighScoreBeatState())
		{
			background->render();
			snake->render();
			food->render();
			if (snake->getGamePausedState() == true && pausedMenu != nullptr)
			{
				pausedMenu->render();
			}
			if (snake->getHighScoreBeatState())
			{
				newHighscoreBox->render();
			}
		}
		
	}

	for (auto itr = pages.begin(); itr != pages.end(); itr++)
	{
		if ((*itr)->getPageType() == GlobalData::currentPage)
		{
			if ((*itr)->getInitializationState())
			{
				(*itr)->render();
				break;
			}
		}
	}
	
	SDL_RenderPresent(renderer);
}



#include "Controller.h"
#include "GlobalData.h"
#include <thread>



Controller::Controller(std::shared_ptr<Snake> snakePtr)
{
	this->snakePtr = snakePtr;
}

Controller::~Controller()
{
	
}


void Controller::moveSnake(const char* texture,int x, int y, const char* directionStr, Direction direction)
{
	
	if (snakeHeadLocation != snakePtr->snakeBody.front()->position)
	{
		snakeHeadLocation = snakePtr->snakeBody.front()->position;
		snakePtr->snakeBody.front()->setTexture(texture);
		snakePtr->prevDirection = snakePtr->snakeDirection;
		snakePtr->prevVector = snakePtr->snakeBody.front()->velocity;
		snakePtr->snakeDirection = direction;
		snakePtr->snakeBody.front()->velocity.x = x;
		snakePtr->snakeBody.front()->velocity.y = y;
		snakePtr->movementStack.emplace_back(Vector2D(x,y));
		std::cout << directionStr << std::endl;	
		
		
	}
	

	// lock move by comparing current location to pass location

	
}

void Controller::gameOverEnterOperation()
{
	switch (GlobalData::currentMenuSelection)
	{
		case 1:
			snakePtr->createSnake();
			GlobalData::currentPage = GamePage::GAME;
			GlobalData::currentMenuSelection = 1;
			GlobalData::isControllerLocked = true;
			break;
		case 2:
			GlobalData::currentMenuSelection = 1;
			GlobalData::currentPage = GamePage::HOME;
			GlobalData::menuOptionChanged = true;
			GlobalData::isControllerLocked = true;
			break;
		case 3:
			Game::isGameRunning = false;
			GlobalData::isControllerLocked = true;
		default:
			break;
	}
}

void Controller::homeEnterOperation()
{
	switch (GlobalData::currentMenuSelection)
	{
		case 1:
			GlobalData::currentPage = GamePage::GAME;
			snakePtr->createSnake();
			GlobalData::isControllerLocked = true;
			break;
		case 2:
			GlobalData::currentPage = GamePage::SETTINGS;
			GlobalData::currentMenuSelection = 1;
			GlobalData::menuOptionChanged = true;
			GlobalData::isControllerLocked = true;
			break;
		case 3:
			GlobalData::currentPage = GamePage::HIGHSCORE;
			GlobalData::currentMenuSelection = 1;
			GlobalData::menuOptionChanged = true;
			GlobalData::isControllerLocked = true;
			break;
		case 4:
			Game::isGameRunning = false;
			GlobalData::isControllerLocked = true;
		default:
			break;
	}
}

void Controller::highscoreEscapeOperation()
{
	GlobalData::currentPage = GamePage::HOME;
	GlobalData::currentMenuSelection = 1;
	GlobalData::menuOptionChanged = true;
	GlobalData::isControllerLocked = true;
}

void Controller::settingsEnterOperation()
{
	switch (GlobalData::currentMenuSelection)
	{
		{
			case 1:
				GlobalData::currentPage = GamePage::MAPSETTINGS;
				GlobalData::currentMenuSelection = 1;
				GlobalData::menuOptionChanged = true;
				GlobalData::isControllerLocked = true;
				break;
			case 2:
				GlobalData::currentPage = GamePage::DIFFICULT;
				GlobalData::currentMenuSelection = 1;
				GlobalData::menuOptionChanged = true;
				GlobalData::isControllerLocked = true;
				break;
			default:
				break;
		}
	}
}

void Controller::settingsEscapeOperation()
{
	GlobalData::currentPage = GamePage::HOME;
	GlobalData::currentMenuSelection = 1;
	GlobalData::menuOptionChanged = true;
	GlobalData::isControllerLocked = true;
}

void Controller::changeSettingsEnterOperation()
{
	if (GlobalData::currentMenuSelection > 0)
	{
		GlobalData::settingsChanged = true;
		GlobalData::isControllerLocked = true;
	}
}

void Controller::changeSettingsEscapeOperation()
{
	GlobalData::currentPage = GamePage::SETTINGS;
	GlobalData::currentMenuSelection = 1;
	GlobalData::menuOptionChanged = true;
	GlobalData::isControllerLocked = true;
}

void Controller::snakeNavigation()
{
		if (!snakePtr->isSnakeDead && !snakePtr->isGamePaused)
		{
			if (Game::event.type == SDL_KEYDOWN)
			{
				switch (Game::event.key.keysym.sym)
				{
					case SDLK_w:
						up();
						GlobalData::isControllerLocked = true;
						break;
					case SDLK_a:
						left();
						GlobalData::isControllerLocked = true;
						break;
					case SDLK_s:
						down();
						GlobalData::isControllerLocked = true;
						break;
					case SDLK_d:
						right();
						GlobalData::isControllerLocked = true;
						break;
					case SDLK_ESCAPE:
						if (!snakePtr->isGamePaused)
						{
							GlobalData::currentMenuSelection = 1;
							snakePtr->pauseSnake();
							std::cout << "Game paused" << std::endl;
							GlobalData::isControllerLocked = true;
						}
						break;
					default:
						break;
				}
			}
		}
		else
		{
			if (snakePtr->isGamePaused)
			{
				menuNavigation(3);
			}
		}


	if (Game::event.type == SDL_KEYUP)
	{
		switch (Game::event.key.keysym.sym)
		{
			case SDLK_w:
				GlobalData::isControllerLocked = false;
				break;
			case SDLK_a:
				GlobalData::isControllerLocked = false;
				break;
			case SDLK_s:
				GlobalData::isControllerLocked = false;
				break;
			case SDLK_d:
				GlobalData::isControllerLocked = false;
				break;
			case SDLK_RETURN:
				GlobalData::isControllerLocked = false;
				break;
			case SDLK_ESCAPE:
				GlobalData::isControllerLocked = false;
				break;
			default:
				break;

		}
	}
	
}

void Controller::difficultyEscapeOperation()
{
	GlobalData::currentPage = GamePage::SETTINGS;
	GlobalData::isControllerLocked = true;
}

void Controller::snakePausedMenuEnterOperation()
{
	switch (GlobalData::currentMenuSelection)
	{
		case 1:
			snakePtr->resumeSnake();
			GlobalData::isControllerLocked = true;
			break;
		case 2:
			GlobalData::currentPage = GamePage::HOME;
			GlobalData::currentMenuSelection = 1;
			GlobalData::menuOptionChanged = true;
			GlobalData::isControllerLocked = true;
			std::cout << "Goto main" << std::endl;
			break;
		case 3:
			Game::isGameRunning = false;
			GlobalData::isControllerLocked = true;
			break;
		default:
			break;
	}
}

void Controller::menuNavigation(int menuItems)
{
	if (Game::event.type == SDL_KEYDOWN)
	{
		if (!GlobalData::isControllerLocked)
		{
			switch (Game::event.key.keysym.sym)
				{
					case SDLK_w:
						if (GlobalData::currentMenuSelection > 1)
						{
							GlobalData::currentMenuSelection--;
							GlobalData::menuOptionChanged = true;
							GlobalData::isControllerLocked = true;
						}
						break;
					case SDLK_s:
						if (GlobalData::currentMenuSelection < menuItems)
						{
							GlobalData::currentMenuSelection++;
							GlobalData::menuOptionChanged = true;
							GlobalData::isControllerLocked = true;
						}
						break;
					case SDLK_ESCAPE:
						if (GlobalData::currentPage == GamePage::HIGHSCORE)
						{
							highscoreEscapeOperation();
						}
						else if (GlobalData::currentPage == GamePage::SETTINGS)
						{
							settingsEscapeOperation();
						}
						else if (GlobalData::currentPage == GamePage::MAPSETTINGS)
						{
							changeSettingsEscapeOperation();
						}
						else if (GlobalData::currentPage == GamePage::DIFFICULT)
						{
							changeSettingsEscapeOperation();
						}
						/*else if (GlobalData::currentPage == GamePage::GAME && snakePtr->isGamePaused)
						{
							snakePtr->resumeSnake();
							GlobalData::isControllerLocked = true;
						}*/
						break;
					case SDLK_RETURN:
						if (GlobalData::currentPage == GamePage::HOME)
						{
							homeEnterOperation();
						}
						else if (GlobalData::currentPage == GamePage::GAMEOVER)
						{
							gameOverEnterOperation();
						}
						else if (GlobalData::currentPage == GamePage::SETTINGS)
						{
							settingsEnterOperation();
						}
						else if (GlobalData::currentPage == GamePage::MAPSETTINGS)
						{
							changeSettingsEnterOperation();
						}
						else if (GlobalData::currentPage == GamePage::DIFFICULT)
						{
							changeSettingsEnterOperation();
						}
						else if (GlobalData::currentPage == GamePage::GAME && snakePtr->isGamePaused == true)
						{
							std::cout << "Yes" << std::endl;
							snakePausedMenuEnterOperation();
							
						}
						break;
					default:
						break;
				}
			
			
		}
		
	}
	if (Game::event.type == SDL_KEYUP)
	{
		if (GlobalData::isControllerLocked)
		{
			switch (Game::event.key.keysym.sym)
			{
				case SDLK_w:
					GlobalData::isControllerLocked = false;
					break;
				case SDLK_s:
					GlobalData::isControllerLocked = false;
					break;
				case SDLK_RETURN:
					GlobalData::isControllerLocked = false;
					break;
				case SDLK_ESCAPE:
					GlobalData::isControllerLocked = false;
					break;
				default:
					break;
			}
		}
	
	}
}

void Controller::up()
{
	//Change snake direction to up if the conditions are met
	if (snakePtr->snakeDirection == Direction::LEFT || snakePtr->snakeDirection == Direction::RIGHT ) {
		if (snakePtr->snakeBody.front()->position.y == snakePtr->snakeBody.at(1)->position.y)
		{
			moveSnake(GlobalData::snakeHeadUpTexture.c_str(), 0, -1, "UP", Direction::UP);
			
		}
		
	}
}

void Controller::down()
{
	// Change snake head direction to down and changes snake head velocity
	if (snakePtr->snakeDirection == Direction::LEFT || snakePtr->snakeDirection == Direction::RIGHT ) {
		if (snakePtr->snakeBody.front()->position.y == snakePtr->snakeBody.at(1)->position.y)
		{
			moveSnake(GlobalData::snakeHeadDownTexture.c_str(), 0, 1, "DOWN", Direction::DOWN);
		}
		
	}
}

void Controller::left()
{
	// Change snake head direction to left and changes snake head velocity
	if (snakePtr->snakeDirection == Direction::UP || snakePtr->snakeDirection == Direction::DOWN) {
		if (snakePtr->snakeBody.front()->position.x == snakePtr->snakeBody.at(1)->position.x)
		{
			moveSnake(GlobalData::snakeHeadLeftTexture.c_str(), -1, 0, "LEFT", Direction::LEFT);
		}
		
	}
}

void Controller::right()
{
	// Change snake head direction to right and changes snake head velocity
	if (snakePtr->snakeDirection == Direction::UP || snakePtr->snakeDirection == Direction::DOWN) {
		if (snakePtr->snakeBody.front()->position.x == snakePtr->snakeBody.at(1)->position.x)
		{
			moveSnake(GlobalData::snakeHeadRightTexture.c_str(), 1, 0, "RIGHT", Direction::RIGHT);
		}
		
	}
}

void Controller::captureInput()
{
	
	if (GlobalData::currentPage == GamePage::GAME)
	{
		// Input for game window
		
		snakeNavigation();
	}
	else if (GlobalData::currentPage == GamePage::HOME)
	{
		menuNavigation(4);
	}
	else if (GlobalData::currentPage == GamePage::GAMEOVER)
	{
		menuNavigation(3);
	}
	else if (GlobalData::currentPage == GamePage::HIGHSCORE)
	{
		menuNavigation(0);
	}
	else if (GlobalData::currentPage == GamePage::SETTINGS)
	{
		menuNavigation(2);
	}
	else if (GlobalData::currentPage == GamePage::MAPSETTINGS)
	{
		menuNavigation(2);
	}
	else if (GlobalData::currentPage == GamePage::DIFFICULT)
	{
		menuNavigation(3);
	}
	
	
}
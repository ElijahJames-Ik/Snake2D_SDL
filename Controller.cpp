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
	snakePtr->snakeBody.front()->setTexture(texture);
	snakePtr->snakeDirection = direction;
	snakePtr->snakeBody.front()->velocity.x = x;
	snakePtr->snakeBody.front()->velocity.y = y;
	std::cout << directionStr << std::endl;
	snakePtr->update();
}

void Controller::up()
{
	//Change snake direction to up if the conditions are met
	if (snakePtr->snakeDirection == Direction::LEFT || snakePtr->snakeDirection == Direction::RIGHT && (*(snakePtr->snakeBody.begin()))->velocity == (*(snakePtr->snakeBody.begin()+2))->velocity) {
		moveSnake("assets/snake_head_up.png", 0, -1, "UP", Direction::UP);
	}
}

void Controller::down()
{
	// Change snake head direction to down and changes snake head velocity
	if (snakePtr->snakeDirection == Direction::LEFT || snakePtr->snakeDirection == Direction::RIGHT && (*(snakePtr->snakeBody.begin()))->velocity == (*(snakePtr->snakeBody.begin()+2))->velocity) {
		moveSnake("assets/snake_head_down.png", 0, 1, "DOWN", Direction::DOWN);
	}
}

void Controller::left()
{
	// Change snake head direction to left and changes snake head velocity
	if (snakePtr->snakeDirection == Direction::UP || snakePtr->snakeDirection == Direction::DOWN && (*(snakePtr->snakeBody.begin()))->velocity == (*(snakePtr->snakeBody.begin()+2))->velocity) {
		moveSnake("assets/snake_head_left.png", -1, 0, "LEFT", Direction::LEFT);
	}
}

void Controller::right()
{
	// Change snake head direction to right and changes snake head velocity
	if (snakePtr->snakeDirection == Direction::UP || snakePtr->snakeDirection == Direction::DOWN && (*(snakePtr->snakeBody.begin()))->velocity == (*(snakePtr->snakeBody.begin() + 2))->velocity) {
		moveSnake("assets/snake_head_right.png", 1, 0, "RIGHT", Direction::RIGHT);
	}
}

void Controller::captureInput()
{
	
	if (GlobalData::currentPage == GamePage::GAME)
	{
		// Input for game window
		if (!snakePtr->isSnakeDead && !snakePtr->isGamePaused)
		{
			if (keyBoardState[SDL_SCANCODE_W])
			{
				up();
			}
			else if (keyBoardState[SDL_SCANCODE_A])
			{
				left();
			}
			else if (keyBoardState[SDL_SCANCODE_S])
			{
				down();
			}
			else if (keyBoardState[SDL_SCANCODE_D])
			{
				right();
			}
			else if (keyBoardState[SDL_SCANCODE_ESCAPE])
			{
				if (!snakePtr->isGamePaused)
				{
					snakePtr->pauseSnake();
				}
				GlobalData::currentMenuSelection = 1;
				std::cout << "Game paused" << std::endl;
			}
		}
		else
		{
			if (snakePtr->isGamePaused)
			{
				if (keyBoardState[SDL_SCANCODE_1])
				{
					GlobalData::currentMenuSelection = 1;
					GlobalData::menuOptionChanged = true;
				}
				else if (keyBoardState[SDL_SCANCODE_2])
				{
					GlobalData::currentMenuSelection = 2;
					GlobalData::menuOptionChanged = true;
				}
				else if (keyBoardState[SDL_SCANCODE_3])
				{
					GlobalData::currentMenuSelection = 3;
					GlobalData::menuOptionChanged = true;
				}
				else if (keyBoardState[SDL_SCANCODE_RETURN])
				{
					if (GlobalData::currentMenuSelection == 1)
					{
						snakePtr->resumeSnake();
					}
					else if (GlobalData::currentMenuSelection == 2)
					{
						GlobalData::currentPage = GamePage::HOME;
						GlobalData::currentMenuSelection = 1;
					}
					else if (GlobalData::currentMenuSelection == 3)
					{
						Game::isGameRunning = false;
					}
				}
			}
		}
	}
	// Input for navigating home window
	else if (GlobalData::currentPage == GamePage::HOME)
	{
		
		if (keyBoardState[SDL_SCANCODE_1])
		{
			GlobalData::currentMenuSelection = 1;
			GlobalData::menuOptionChanged = true;
		}
		else if (keyBoardState[SDL_SCANCODE_2])
		{
			GlobalData::currentMenuSelection = 2;
			GlobalData::menuOptionChanged = true;
		}
		else if (keyBoardState[SDL_SCANCODE_3])
		{
			GlobalData::currentMenuSelection = 3;
			GlobalData::menuOptionChanged = true;
		}
		else if (keyBoardState[SDL_SCANCODE_4])
		{
			GlobalData::currentMenuSelection = 4;
			GlobalData::menuOptionChanged = true;
		}
		else if (keyBoardState[SDL_SCANCODE_RETURN])
		{
			switch (GlobalData::currentMenuSelection)
			{
			case 1:
				GlobalData::currentPage = GamePage::GAME;
				GlobalData::currentMenuSelection = 1;
				snakePtr->createSnake();
				break;
			case 4:
				Game::isGameRunning = false;
			default:
				break;
			}
		}
	}
	// input for navigating gameover page
	else if (GlobalData::currentPage == GamePage::GAMEOVER)
	{
		
		if (keyBoardState[SDL_SCANCODE_1])
		{
			GlobalData::currentMenuSelection = 1;
			GlobalData::menuOptionChanged = true;
		}
		else if (keyBoardState[SDL_SCANCODE_2])
		{
			GlobalData::currentMenuSelection = 2;
			GlobalData::menuOptionChanged = true;
		}
		else if (keyBoardState[SDL_SCANCODE_3])
		{
			GlobalData::currentMenuSelection = 3;
			GlobalData::menuOptionChanged = true;
		}
		else if (keyBoardState[SDL_SCANCODE_RETURN])
		{
			switch (GlobalData::currentMenuSelection)
			{
			case 1:
				snakePtr->createSnake();
				GlobalData::currentPage = GamePage::GAME;
				GlobalData::currentMenuSelection = 1;
				break;
			case 2:
				GlobalData::currentPage = GamePage::HOME;
				break;
			case 3:
				Game::isGameRunning = false;
			default:
				break;
			}
		}
	}
	
	
	
}
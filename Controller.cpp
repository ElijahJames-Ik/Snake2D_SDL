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

//Change snake head direction
void Controller::moveSnake(const char* texture,int x, int y, const char* directionStr, Direction direction)
{
	
	if (snakeHeadLocation != snakePtr->snakeBody.front()->position)
	{
		snakeHeadLocation = snakePtr->snakeBody.front()->position;
		snakePtr->snakeBody.front()->setTexture(texture);
		//snakePtr->prevDirection = snakePtr->snakeDirection;
		//snakePtr->prevVector = snakePtr->snakeBody.front()->velocity;
		snakePtr->snakeDirection = direction;
		snakePtr->snakeBody.front()->velocity.x = x;
		snakePtr->snakeBody.front()->velocity.y = y;
		snakePtr->movementStack.emplace_back(Vector2D(x,y));	
	}
	
}

// handles enter key operation for gameover screen
void Controller::gameOverEnterOperation()
{
	switch (GlobalData::currentMenuSelection)
	{
		case 1:
			snakePtr->createSnake();
			GlobalData::isFoodManagerResetRequired = true;
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

// handles enter key operation for home screen
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

// handles escape key operation for highscore screen
void Controller::highscoreEscapeOperation()
{
	GlobalData::currentPage = GamePage::HOME;
	GlobalData::currentMenuSelection = 1;
	GlobalData::menuOptionChanged = true;
	GlobalData::isControllerLocked = true;
}

// handles enter key operation for settings screen
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

// handles escape key operation for settings screen
void Controller::settingsEscapeOperation()
{
	GlobalData::currentPage = GamePage::HOME;
	GlobalData::currentMenuSelection = 1;
	GlobalData::menuOptionChanged = true;
	GlobalData::isControllerLocked = true;
}

// handles enter key operation for change game map screen
void Controller::changeSettingsEnterOperation()
{
	if (GlobalData::currentMenuSelection > 0)
	{
		GlobalData::settingsChanged = true;
		GlobalData::isControllerLocked = true;
	}
}

// handles escape key operation for change game map screen
void Controller::changeSettingsEscapeOperation()
{
	GlobalData::currentPage = GamePage::SETTINGS;
	GlobalData::currentMenuSelection = 1;
	GlobalData::menuOptionChanged = true;
	GlobalData::isControllerLocked = true;
}

// handles snake movement
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
							GlobalData::menuOptionChanged = true;
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
			if (snakePtr->isGamePaused == true)
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

// handles escape key operation for difficulty settings page
void Controller::difficultyEscapeOperation()
{
	GlobalData::currentPage = GamePage::SETTINGS;
	GlobalData::isControllerLocked = true;
}

// handles enter key operation for paused menu screen
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
			snakePtr->isTitleUpdateRequried = true;
			GlobalData::windowTitle = "SNAKE";
			break;
		case 3:
			Game::isGameRunning = false;
			GlobalData::isControllerLocked = true;
			break;
		default:
			break;
	}
}

// handles menu navigation for all screens with options
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
						else if (GlobalData::currentPage == GamePage::GAME && snakePtr->isGamePaused )
						{
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

// change snake head direction to up
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

// change snake head direction to down
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

// change snake head direction to left
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

// change snake head direction to right
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

// handle game inputs
void Controller::captureInput()
{
	while (SDL_PollEvent(&Game::event) != 0)
	{
		if (Game::event.type == SDL_QUIT)
		{
			Game::isGameRunning = false;
		}
		else if (Game::event.type == SDL_TEXTINPUT && snakePtr->isHighScoreBeat)
		{



			if (!(SDL_GetModState() & KMOD_CTRL && (Game::event.text.text[0] == 'c' || Game::event.text.text[0] == 'C' || Game::event.text.text[0] == 'v' || Game::event.text.text[0] == 'V')))
			{
				if (GlobalData::enteredNameTextField.length() < 4)
				{
					GlobalData::enteredNameTextField += Game::event.text.text;
					std::cout << GlobalData::enteredNameTextField << std::endl;
					GlobalData::isInputTextToBeRedrawn = true;
				}

			}


		}
		else
		{
			if (GlobalData::currentPage == GamePage::GAME)
			{
				// Input for game window
				if (!snakePtr->isSnakeDead)
				{
					snakeNavigation();
				}
				else
				{
					if (snakePtr->isHighScoreBeat)
					{
						handleEditBoxInput();
					}
				}

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
	}




	
	
	
}

// handle edit box input when user beats any highscore
void Controller::handleEditBoxInput()
{
	if (Game::event.type == SDL_KEYDOWN)
	{
		if (Game::event.key.keysym.sym == SDLK_BACKSPACE && GlobalData::enteredNameTextField.length() > 0)
		{
			GlobalData::enteredNameTextField.pop_back();
			GlobalData::isInputTextToBeRedrawn = true;
			std::cout << "BackSpace" << std::endl;
		}
		else if (Game::event.key.keysym.sym == SDLK_RETURN)
		{
			saveHighScoreOperation();
		}
	}
	else
	{

	}
	
}

void Controller::saveHighScoreOperation()
{
	std::cout << "Yes" << "-> " << GlobalData::enteredNameTextField.length() << std::endl;
	if (GlobalData::enteredNameTextField.length() == 4)
	{
		std::string username = GlobalData::enteredNameTextField.substr(1);
		DataProvider provider;
		
		std::vector<std::string> highscoreList = provider.getHighscoresAsListOfStrings(GlobalData::highscoreFile);
		int count;
		for (auto itr = highscoreList.begin(); itr != highscoreList.end(); itr++)
		{
		
			size_t pos = (*itr).find("=");
			pos++;
			int score = std::stoi((*itr).substr(pos));
			if (GlobalData::score > score)
			{
				if (itr == highscoreList.end() - 1)
				{
					(*itr) = GlobalData::enteredNameTextField.substr(1) + "=" + std::to_string(GlobalData::score);
				}
				else
				{
					highscoreList.insert(itr, GlobalData::enteredNameTextField.substr(1) + "=" + std::to_string(GlobalData::score));
					highscoreList.pop_back();
				}
				
				provider.writeData(GlobalData::highscoreFile, highscoreList);
				GlobalData::isHighscoreLoadRequired = true;
				break;
			}
		}

		GlobalData::currentPage = GamePage::GAMEOVER;
		GlobalData::currentMenuSelection = 1;
		GlobalData::menuOptionChanged = true;
		GlobalData::isGameOver = true;
	}
}
#include "Snake.h"
#include "Collision.h"
#include "GlobalData.h"







Snake::Snake(int size):snakeSize(size)
{
}

void Snake::createSnake()
{
	int startX = Game::windowWidth / 2 + (snakeSize * 8);
	int startY = Game::windowHeight/2 - 4;

	snakeBody.clear();
	snakeDirection = Direction::RIGHT;
	isSnakeDead = false;
	isGamePaused = false;
	isHighScoreBeat = false;
	GlobalData::score = 0;
	
	snakeBody.emplace_back(std::make_unique<SnakeBody>(GlobalData::snakeHeadRightTexture.c_str(), startX, startY, GlobalData::bodyWidth, GlobalData::bodyHeight));
	
	
	for (int i = 0; i < snakeSize; i++)
	{
		startX -= 8;
		auto body = std::make_unique<SnakeBody>(GlobalData::snakeBodyTexture.c_str(), startX, startY, GlobalData::bodyWidth, GlobalData::bodyHeight);
		snakeBody.emplace_back(std::move(body));
	}
}

bool Snake::getSnakeState()
{
	return isSnakeDead;
}
void Snake::setSnakeState(bool state)
{
	isSnakeDead = state;
}

bool Snake::getGamePausedState()
{
	return isGamePaused;
}
void Snake::setGamePausedState(bool state)
{
	isGamePaused = state;
}

bool Snake::getHighScoreBeatState()
{
	return isHighScoreBeat;
}
void Snake::setHighScoreBeatState(bool state)
{
	isHighScoreBeat = state;
}

bool Snake::getTitleUpdateState()
{
	return isTitleUpdateRequried;
}
void Snake::setTitleUpdateState(bool state)
{
	isTitleUpdateRequried = state;
}

void Snake::addBonus(int bonus)
{
	GlobalData::score += bonus;
	GlobalData::windowTitle = "SNAKE    SCORE: " + std::to_string(GlobalData::score);
	isTitleUpdateRequried = true;
	
}

// increase the snake size after eating snake food
void Snake::growSnake()
{
	
	GlobalData::score += 5;
	GlobalData::windowTitle = "SNAKE    SCORE: " + std::to_string(GlobalData::score);
	isTitleUpdateRequried = true;
	// get current snake head coordinates
	int startX = snakeBody.front()->getPosition().x;
	int startY = snakeBody.front()->getPosition().y;
	
	// move snake head object
	switch (snakeDirection)
	{
		case Direction::UP:
			snakeBody.front()->getPosition().y += -GlobalData::bodyHeight;
			break;
		case Direction::DOWN:
			snakeBody.front()->getPosition().y += GlobalData::bodyHeight;
			break;
		case Direction::LEFT:
			snakeBody.front()->getPosition().x += -GlobalData::bodyWidth;
			break;
		case Direction::RIGHT:
			snakeBody.front()->getPosition().x += GlobalData::bodyWidth;
			break;

	}
	// insert new snake body before snake head.
	auto body = std::make_unique<SnakeBody>(GlobalData::snakeBodyTexture.c_str(), startX, startY, GlobalData::bodyWidth, GlobalData::bodyHeight);
	snakeBody.insert(snakeBody.begin() + 1, std::move(body));
	update();
}

int Snake::getScore()
{
	return GlobalData::score;
}

void Snake::pauseSnake()
{
	isGamePaused = true;
	for (auto itr = snakeBody.begin(); itr != snakeBody.end(); itr++)
	{
		(*itr)->pauseMovement();
	}
}

void Snake::resumeSnake()
{
	isGamePaused = false;
	for (auto itr = snakeBody.begin(); itr != snakeBody.end(); itr++)
	{
		(*itr)->resumeMovement();
	}
}

void Snake::updateSnakeBody()
{
	for (auto itr = snakeBody.begin(); itr != snakeBody.end(); itr++)
	{
		// update snakebody items based on the velocity of the previous item
		
		if (itr != snakeBody.begin())
		{
			
			if ((*itr)->getVelocity() != (*(itr - 1))->getVelocity())
			{
				if ((*itr)->getPosition().x == (*(itr - 1))->getPosition().x || (*itr)->getPosition().y == (*(itr - 1))->getPosition().y )
				{
						(*itr)->setVelocity((*(itr - 1))->getVelocity());	
				}
			}

		}
		(*itr)->update();
		if (itr > snakeBody.begin() + 1)
		{
			if (Collision::CheckForCollision(snakeBody.front()->getDestRect(), (*itr)->getDestRect()) == true)
			{
				std::cout << "Snake is dead" << std::endl;
				(*snakeBody.begin())->setVelocity(Vector2D());
				isSnakeDead = true;
				GlobalData::windowTitle = "SNAKE";
				isTitleUpdateRequried = true;
				checKifHighscoreIsBeat();
				// check if user beat any highscore
				
				break;
			}
		}
		
	}
}

void Snake::checKifHighscoreIsBeat()
{
	DataProvider provider;
	std::vector<int> highscoreList = provider.getHighscores(GlobalData::highscoreFile);

	for (auto itr = highscoreList.begin(); itr != highscoreList.end(); itr++)
	{
		if (GlobalData::score > (*itr))
		{
			isHighScoreBeat = true;
			break;
		}
	}
	if (!isHighScoreBeat)
	{
		GlobalData::currentPage = GamePage::GAMEOVER;
		GlobalData::currentMenuSelection = 1;
		GlobalData::menuOptionChanged = true;
		GlobalData::isGameOver = true;
	}
}

void Snake::moveSnake(const char* texture, int x, int y, const char* directionStr, Direction direction, Direction oppositeDirection, Direction newDirection)
{
	if (snakeDirection == direction || snakeDirection == oppositeDirection) {
		if (Collision::CheckForCollision(snakeBody.front()->getDestRect(), snakeBody.at(1)->getDestRect()) == false && snakeBody.front()->getVelocity() == snakeBody.at(1)->getVelocity())
		{
			std::cout << directionStr << std::endl;
			if (snakeHeadLocation != snakeBody.front()->getPosition() )
			{
				snakeHeadLocation = snakeBody.front()->getPosition();
				snakeBody.front()->setTexture(texture);
				previousVector = snakeBody.front()->getVelocity();
				snakeDirection = newDirection;
				snakeBody.front()->setVelocity(Vector2D(x, y));
				updateSnakeBody();
				
			}
		}
	}

}

bool Snake::checkIfSnakeFoodIsEaten(std::unique_ptr<SnakeFood>& food)
{
	if (Collision::CheckForCollision(snakeBody.front()->getDestRect(), food->getDestRect()) == true)
	{
		food->setFoodState(true);
		growSnake();
		std::cout << "Snake Food Eaten" << std::endl;
		return true;
	}
	return false;
}

bool Snake::checkIfBonusFoodIsEaten(std::unique_ptr<SnakeFood>& bonus)
{
	if (Collision::CheckForCollision(snakeBody.front()->getDestRect(), bonus->getDestRect()) == true)
	{
		bonus->setFoodState(true);
		addBonus(50);
		std::cout << "Bonus Eaten" << std::endl;
		return true;
	}
	return false;
}

void Snake::checkIfSnakeCollidiesWithBoxedInMap(std::unique_ptr<WorldMap>& background)
{
	if (GlobalData::currentGameMap == MapType::BOXED_IN)
	{
		if (background->getCollisionBoxesList().size() > 0 && !getSnakeState())
		{
			
			for (auto itr = background->getCollisionBoxesList().begin(); itr != background->getCollisionBoxesList().end(); itr++)
			{
				if (Collision::CheckForCollision(snakeBody.front()->getDestRect(), (*itr)->getDestRect()) == true)
				{
					std::cout << "Snake is dead" << std::endl;
					std::cout << (*itr)->getDestRect().x << std::endl;
					snakeBody.front()->getVelocity().x = 0;
					snakeBody.front()->getVelocity().y = 0;
					setSnakeState(true);
					checKifHighscoreIsBeat();

					break;

				}
			}
		}

	}
}

bool Snake::checkIfFoodNewLocationCollidesWithSnakeBody(SDL_Rect newPosition)
{
	for (auto itr = snakeBody.begin(); itr != snakeBody.end(); itr++)
	{
		// check if new food location collides with snake body
		if (Collision::CheckForCollision((*itr)->getDestRect(), newPosition) == true)
		{
			return true;
		}
	}
	return false;
}

void Snake::update()
{
	if (isSnakeDead == false)
	{
		updateSnakeBody();
	}
	
	
}

void Snake::render()
{
	for (auto it = snakeBody.begin(); it != snakeBody.end(); it++)
	{
		(*it)->render();
	}
}
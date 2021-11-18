#include "Snake.h"
#include "Collision.h"






Snake::Snake(int size)
{
	snakeSize = size;
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

void Snake::addBonus(int bonus)
{
	GlobalData::score += bonus;
	GlobalData::windowTitle = "SNAKE    SCORE: " + std::to_string(GlobalData::score);
	isTitleUpdateRequried = true;
	
}

// increase the snake size after eating snake food
void Snake::growSnake()
{
	//isSnakeGrowing = true;
	GlobalData::score += 5;
	GlobalData::windowTitle = "SNAKE    SCORE: " + std::to_string(GlobalData::score);
	isTitleUpdateRequried = true;
	// get current snake head coordinates
	int startX = snakeBody.front()->position.x;
	int startY = snakeBody.front()->position.y;
	
	// move snake head object
	switch (snakeDirection)
	{
		case Direction::UP:
			snakeBody.front()->position.y += -GlobalData::bodyHeight;
			break;
		case Direction::DOWN:
			snakeBody.front()->position.y += GlobalData::bodyHeight;
			break;
		case Direction::LEFT:
			snakeBody.front()->position.x += -GlobalData::bodyWidth;
			break;
		case Direction::RIGHT:
			snakeBody.front()->position.x += GlobalData::bodyWidth;
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
	snakeBody.front()->update();
	for (auto itr = snakeBody.begin()+1; itr != snakeBody.end(); itr++)
	{
		

		// update snakebody items based on the velocity of the previous item
		if ((*itr)->velocity != (*(itr - 1))->velocity)
		{
			if ((*itr)->position.x == (*(itr - 1))->position.x || (*itr)->position.y == (*(itr - 1))->position.y)
			{
					(*itr)->velocity = (*(itr - 1))->velocity;
			}
		}
		if (itr > snakeBody.begin() + 2)
		{
			if (Collision::AABB(snakeBody.front()->destRect, (*itr)->destRect) == true)
			{
				std::cout << "Snake is dead" << std::endl;
				(*snakeBody.begin())->velocity.x = 0;
				(*snakeBody.begin())->velocity.y = 0;
				isSnakeDead = true;
				GlobalData::windowTitle = "SNAKE";
				isTitleUpdateRequried = true;
				checKifHighscoreIsBeat();
				// check if user beat any highscore
				
				break;
			}
		}
		(*itr)->update();	
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
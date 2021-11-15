#include "Snake.h"
#include "Collision.h"
#include "GlobalData.h"


void Snake::updateSnake()
{

	int prev_x = snakeBody.front()->position.x;
	int prev_y = snakeBody.front()->position.y;
	updateHead();
	int current_x = snakeBody.front()->position.x;
	int current_y = snakeBody.front()->position.y;
	std::cout << current_x << " " << prev_x << std::endl;
	if (current_x != prev_x || current_y != prev_y)
	{
		updateBody(std::make_unique<SnakeBody>(GlobalData::snakeBodyTexture.c_str(), prev_x, prev_y, GlobalData::bodyWidth, GlobalData::bodyHeight));

	}
}

void Snake::updateBody(std::unique_ptr<SnakeBody>&& body)
{
	snakeBody.emplace_back(std::move(body));

	if (!isSnakeGrowing)
	{
		snakeBody.erase(snakeBody.end()-1);
	}
	else {
		isSnakeGrowing = false;
		score += 5;
	}

	checkIfSnakeBitItsSelf();
	
}

void Snake::updateHead()
{
	snakeBody.front()->update();
}

void Snake::checkIfSnakeBitItsSelf()
{
	for (auto itr = snakeBody.begin() + 1; itr != snakeBody.end(); itr++)
	{
		if (Collision::AABB(snakeBody.front()->destRect, (*itr)->destRect) == true)
		{
			std::cout << "Snake is dead" << std::endl;
			std::cout << "X:" << snakeBody.front()->position.x << "|" << (*itr)->position.x << std::endl;
			std::cout << "Y:" << snakeBody.front()->position.y << "|" << (*itr)->position.y << std::endl;
			(*snakeBody.begin())->velocity.x = 0;
			(*snakeBody.begin())->velocity.y = 0;
			isSnakeDead = true;
			GlobalData::currentPage = GamePage::GAMEOVER;
			GlobalData::currentMenuSelection = 1;
			GlobalData::menuOptionChanged = true;
			break;
		}
	}
}


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
	score = 0;
	
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
	score += bonus;
}

// increase the snake size after eating snake food
void Snake::growSnake()
{
	//isSnakeGrowing = true;
	score += 5;
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
	return score;
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
	std::cout << "Head" << snakeBody.front()->position.x << "--" << snakeBody.front()->position.y << std::endl;
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
				std::cout << "X:" << snakeBody.front()->position.x << "|" << (*itr)->position.x << std::endl;
				std::cout << "Y:" << snakeBody.front()->position.y << "|" << (*itr)->position.y << std::endl;
				(*snakeBody.begin())->velocity.x = 0;
				(*snakeBody.begin())->velocity.y = 0;
				isSnakeDead = true;
				GlobalData::currentPage = GamePage::GAMEOVER;
				GlobalData::currentMenuSelection = 1;
				GlobalData::menuOptionChanged = true;
				break;
			}
		}
		(*itr)->update();	
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
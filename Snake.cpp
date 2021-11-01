#include "Snake.h"
#include "Collision.h"
#include "GlobalData.h"



const int bodyWidth = 8;
const int bodyHeight = 8;

Snake::Snake(int size)
{
	snakeSize = size;
}

void Snake::createSnake()
{
	int startX = 10 + (snakeSize * 8);
	int startY = Game::windowHeight/2 - 4;

	snakeBody.clear();
	snakeDirection = Direction::RIGHT;
	isSnakeDead = false;
	
	snakeBody.emplace_back(std::make_unique<SnakeBody>("assets/snake_head_right.png", startX, startY, bodyWidth, bodyHeight));
	
	
	for (int i = 0; i < snakeSize; i++)
	{
		startX -= 8;
		auto body = std::make_unique<SnakeBody>("assets/snake_cube.png", startX, startY, bodyWidth, bodyHeight);
		snakeBody.emplace_back(std::move(body));
	}
	

}

void Snake::growSnake()
{
	score += 5;
	int startX = snakeBody.front()->position.x;
	int startY = snakeBody.front()->position.y;
	
	switch (snakeDirection)
	{
	case Direction::UP:
		snakeBody.front()->position.y += -bodyHeight;
		break;
	case Direction::DOWN:
		snakeBody.front()->position.y += bodyHeight;
		break;
	case Direction::LEFT:
		snakeBody.front()->position.x += -bodyWidth;
		break;
	case Direction::RIGHT:
		snakeBody.front()->position.x += bodyWidth;
		break;

	}

	auto body = std::make_unique<SnakeBody>("assets/snake_cube.png", startX, startY, bodyWidth, bodyHeight);
	snakeBody.insert(snakeBody.begin() + 1, std::move(body));
}

int Snake::getScore()
{
	return score;
}

void Snake::pauseSnake()
{
	isGamePaused = true;
	pausedState = snakeBody.front()->velocity;
	snakeBody.front()->velocity = Vector2D();
}

void Snake::resumeSnake()
{
	isGamePaused = false;
	snakeBody.front()->velocity = pausedState;
}



void Snake::update()
{
	if (isSnakeDead == false)
	{
		//update snake 
		for (auto it = snakeBody.begin(); it != snakeBody.end(); it++)
		{
			if (it != snakeBody.begin())
			{
				if ((*it)->velocity != (*(it - 1))->velocity)
				{

					if ((*it)->position.x == (*(it - 1))->position.x)
					{
						(*it)->velocity = (*(it - 1))->velocity;
					}
					else if ((*it)->position.y == (*(it - 1))->position.y)
					{
						(*it)->velocity = (*(it - 1))->velocity;
					}
				}

			}
			(*it)->update();
		}
		for (auto itr = snakeBody.begin() + 3; itr != snakeBody.end(); itr++)
		{
			if (Collision::AABB( snakeBody.front()->destRect, (*itr)->destRect) == true )
			{
				std::cout << "Snake is dead" << std::endl;
				std::cout << "X:" << snakeBody.front()->position.x << "|" << (*itr)->position.x << std::endl;
				std::cout << "Y:" << snakeBody.front()->position.y << "|" << (*itr)->position.y << std::endl;
				(*snakeBody.begin())->velocity.x = 0;
				(*snakeBody.begin())->velocity.y = 0;
				isSnakeDead = true;
				GlobalData::currentPage = GamePage::GAMEOVER;
				GlobalData::currentMenuSelection = 1;	
			}
		}

		


	}
	
	
}

void Snake::render()
{
	for (auto it = snakeBody.begin(); it != snakeBody.end(); it++)
	{
		(*it)->render();
	}
}
#include "Snake.h"
#include "Controller.h"

std::unique_ptr<Controller> controller = nullptr;

Snake::Snake(int size)
{
	snakeSize = size;
}

void Snake::createSnake()
{
	int startX = 10 + (snakeSize * 8);
	int startY = 100;

	
	snakeBody.emplace_back(std::make_unique<SnakeHead>("assets/snake_head_right.png", startX, startY));
	
	
	for (int i = 0; i < snakeSize; i++)
	{
		startX -= 8;
		auto body = std::make_unique<SnakeBody>("assets/snake_cube.png", startX, startY);
		snakeBody.emplace_back(std::move(body));
	}
	controller = std::make_unique<Controller>(this->shared_from_this());

}



void Snake::update()
{
	controller->captureInput();
	for (auto it = snakeBody.begin(); it != snakeBody.end(); ++it)
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
	
}

void Snake::render()
{
	for (auto it = snakeBody.begin(); it != snakeBody.end(); ++it)
	{
		(*it)->render();
	}
}
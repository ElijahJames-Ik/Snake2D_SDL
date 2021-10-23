#include "Snake.h"


Snake::Snake()
{
	snakeSize = 5;
}

void Snake::createSnake()
{
	int startX = 60;
	int startY = 100;
	
	//std::unique_ptr<SnakeHead> head = std::make_unique<SnakeHead>("assets/snake_head.png", startX, startY);
	//snakeBody.emplace_back(std::move(head));
	//
	//
	//for (int i = 0; i < 5; i++)
	//{
	//	startX -= 8;
	//	std::unique_ptr<SnakeHead> body = std::make_unique<SnakeHead>("assets/snake_cube.png", startX, startY);
	//	snakeBody.emplace_back(std::move(body));
	//}
	
}

void Snake::setDirection(Direction direction)
{
	this->snakeDirection = direction;
}

Direction Snake::getDirection()
{
	return snakeDirection;

}

void Snake::updateSnake()
{

}
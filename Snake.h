#pragma once
#include "SnakeBody.h"
#include "SnakeHead.h"
#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;
enum class Direction { UP, DOWN, LEFT, RIGHT };
class Snake
{
public:
	Snake();
	void createSnake();
	void updateSnake();
	Direction getDirection();
	void setDirection(Direction direction);
	vector<unique_ptr<Actor>> snakeBody;
private:
	int snakeSize;
	Direction snakeDirection = Direction::LEFT;
	
	
};
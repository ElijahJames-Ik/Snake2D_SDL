#pragma once
#include "SnakeBody.h"
#include <vector>
#include <memory>


using std::vector;

enum class Direction { UP, DOWN, LEFT, RIGHT };
class Snake : public std::enable_shared_from_this<Snake>
{
public:
	Snake(int size);
	
	void update();
	void render();
	Direction snakeDirection = Direction::LEFT;
	void createSnake();
	void growSnake();
	void pauseSnake();
	void resumeSnake();
	int getScore();

	bool isSnakeDead = false;
	bool isGamePaused = false;
	vector<std::unique_ptr<Actor>> snakeBody;
private:
	int snakeSize;
	int score = 0;
	Vector2D pausedState;

	
	
	

	
	
	
	
	
};
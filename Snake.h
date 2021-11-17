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
	Direction prevDirection = Direction::LEFT;
	void createSnake();
	void growSnake();
	void addBonus(int bonus);
	void pauseSnake();
	void resumeSnake();
	void updateSnakeBody();
	void checKifHighscoreIsBeat();
	int getScore();

	bool isSnakeDead = false;
	bool isGamePaused = false;
	bool isSnakeGrowing = false;
	bool isHighScoreBeat = false;
	bool isTitleUpdateRequried = false;
	vector<std::unique_ptr<SnakeBody>> snakeBody;
	vector<Vector2D> movementStack;
	Vector2D prevVector;
private:
	int snakeSize;
	Vector2D pausedState;


	
	
	

	
	
	
	
	
};
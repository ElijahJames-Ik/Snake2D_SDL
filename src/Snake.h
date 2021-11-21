#pragma once
#include "SnakeBody.h"
#include "WorldMap.h"
#include "SnakeFood.h"
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
	
	void createSnake();
	// grow snake body
	void growSnake();
	void addBonus(int bonus);
	// pause game
	void pauseSnake();
	// resume game
	void resumeSnake();
	void updateSnakeBody();
	// Check if user has beat any highscore
	void checKifHighscoreIsBeat();
	// change snake current direction
	void moveSnake(const char* texture, int x, int y, const char* directionStr, Direction direction, Direction oppositeDirection, Direction newDirection);
	void checkIfSnakeCollidiesWithBoxedInMap(std::unique_ptr<WorldMap>& background);
	// Check if snake has eaten food.
	bool checkIfSnakeFoodIsEaten(std::unique_ptr<SnakeFood>& food);
	// Check if snake has eaten bonus food.
	bool checkIfBonusFoodIsEaten(std::unique_ptr<SnakeFood>& bonus);
	// Check if new food location collides with snake body for place new snake
	// food in a new location.
	bool checkIfFoodNewLocationCollidesWithSnakeBody(SDL_Rect newPosition);
	// Get current game score
	int getScore();
	// Check if snake is still alive
	bool getSnakeState();
	// Set snake current state
	void setSnakeState(bool state);
	// Get game paused state
	bool getGamePausedState();
	// Set game paused state
	void setGamePausedState(bool state);
	// Check if highscore is beat state
	bool getHighScoreBeatState();
	// Set high score beat state
	void setHighScoreBeatState(bool state);
	// Get title update state
	bool getTitleUpdateState();
	// Set title update state
	void setTitleUpdateState(bool state);

	

	
	
private:
	int snakeSize;
	Vector2D pausedState;
	Vector2D snakeHeadLocation;
	Vector2D previousVector;
	vector<std::unique_ptr<SnakeBody>> snakeBody;
	Vector2D prevVector;
	bool isSnakeDead = false;
	bool isGamePaused = false;
	bool isHighScoreBeat = false;
	bool isTitleUpdateRequried = false;
	Direction snakeDirection = Direction::LEFT;
	Direction prevDirection = Direction::LEFT;


	
	
	

	
	
	
	
	
};
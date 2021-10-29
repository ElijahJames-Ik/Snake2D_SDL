#include "Controller.h"



Controller::Controller(std::shared_ptr<Snake> snakePtr)
{
	this->snakePtr = snakePtr;
}

Controller::~Controller()
{
	
}

void Controller::up()
{
	if (snakePtr->snakeDirection == Direction::LEFT || snakePtr->snakeDirection == Direction::RIGHT && (*(snakePtr->snakeBody.begin()))->velocity == (*(snakePtr->snakeBody.begin()+1))->velocity) {
		snakePtr->snakeDirection = Direction::UP;
		snakePtr->snakeBody.front()->velocity.x = 0;
		snakePtr->snakeBody.front()->velocity.y = -1;
		snakePtr->snakeBody.front()->setTexture("assets/snake_head_up.png");
		std::cout << "UP" << std::endl;
		snakePtr->update();
		
	}
}

void Controller::down()
{
	// Change snake head direction to 
	if (snakePtr->snakeDirection == Direction::LEFT || snakePtr->snakeDirection == Direction::RIGHT && (*(snakePtr->snakeBody.begin()))->velocity == (*(snakePtr->snakeBody.begin()+1))->velocity) {
		snakePtr->snakeDirection = Direction::DOWN;
		snakePtr->snakeBody.front()->setTexture("assets/snake_head_down.png");
		snakePtr->snakeBody.front()->velocity.x = 0;
		snakePtr->snakeBody.front()->velocity.y = 1;
		std::cout << "DOWN" << std::endl;
		snakePtr->update();
	}
}

void Controller::left()
{
	if (snakePtr->snakeDirection == Direction::UP || snakePtr->snakeDirection == Direction::DOWN && (*(snakePtr->snakeBody.begin()))->velocity == (*(snakePtr->snakeBody.begin()+1))->velocity) {
		snakePtr->snakeDirection = Direction::LEFT;
		snakePtr->snakeBody.front()->setTexture("assets/snake_head_left.png");
		snakePtr->snakeBody.front()->velocity.x = -1;
		snakePtr->snakeBody.front()->velocity.y = 0;
		std::cout << "LEFT" << std::endl;
		snakePtr->update();

	}
}

void Controller::right()
{
	if (snakePtr->snakeDirection == Direction::UP || snakePtr->snakeDirection == Direction::DOWN && (*(snakePtr->snakeBody.begin()))->velocity == (*(snakePtr->snakeBody.begin() + 1))->velocity) {
		snakePtr->snakeDirection = Direction::RIGHT;
		snakePtr->snakeBody.front()->setTexture("assets/snake_head_right.png");
		snakePtr->snakeBody.front()->velocity.x = 1;
		snakePtr->snakeBody.front()->velocity.y = 0;
		std::cout << "RIGHT" << std::endl;
		snakePtr->update();
	}
}

void Controller::captureInput()
{
	if (snakePtr->isSnakeDead == false)
	{
		if (keyBoardState[SDL_SCANCODE_W])
		{
			up();
		}
		else if (keyBoardState[SDL_SCANCODE_A])
		{
			left();
		}
		else if (keyBoardState[SDL_SCANCODE_S])
		{
			down();
		}
		else if (keyBoardState[SDL_SCANCODE_D])
		{
			right();
		}
	}
	
	
}
#include "Controller.h"



Controller::Controller(std::shared_ptr<Snake> snakePtr)
{
	this->snakePtr = snakePtr;
}



void Controller::captureInput()
{
	if (Game::event.type == SDL_KEYDOWN)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_w:
			if (snakePtr->snakeDirection == Direction::LEFT || snakePtr->snakeDirection == Direction::RIGHT) {
				snakePtr->snakeDirection = Direction::UP;
				std::cout << "UP" << std::endl;
			}		
			break;
		case SDLK_a:
			if (snakePtr->snakeDirection == Direction::UP || snakePtr->snakeDirection == Direction::DOWN) {
				snakePtr->snakeDirection = Direction::LEFT;
				std::cout << "LEFT" << std::endl;
			}
			break;
		case SDLK_s:
			if (snakePtr->snakeDirection == Direction::LEFT || snakePtr->snakeDirection == Direction::RIGHT) {
				snakePtr->snakeDirection = Direction::DOWN;
				std::cout << "DOWN" << std::endl;
			}
			break;
		case SDLK_d:
			if (snakePtr->snakeDirection == Direction::UP || snakePtr->snakeDirection == Direction::DOWN) {
				snakePtr->snakeDirection = Direction::RIGHT;
				std::cout << "RIGHT" << std::endl;
			}
			break;
		}
	}


}
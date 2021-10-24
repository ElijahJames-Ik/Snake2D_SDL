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
				snakePtr->snakeBody.front()->velocity.x = 0;
				snakePtr->snakeBody.front()->velocity.y = -1;
				snakePtr->snakeBody.front()->setTexture("assets/snake_head_up.png");
				snakePtr->snakeBody.front()->flipTexture = SDL_FLIP_NONE;
				
				std::cout << "UP" << std::endl;
			}		
			break;
		case SDLK_a:
			if (snakePtr->snakeDirection == Direction::UP || snakePtr->snakeDirection == Direction::DOWN) {
				snakePtr->snakeDirection = Direction::LEFT;
				snakePtr->snakeBody.front()->velocity.x = -1;
				snakePtr->snakeBody.front()->velocity.y = 0;
				std::cout << "LEFT" << std::endl;
				snakePtr->snakeBody.front()->setTexture("assets/snake_head_left.png");
				
			}
			break;
		case SDLK_s:
			if (snakePtr->snakeDirection == Direction::LEFT || snakePtr->snakeDirection == Direction::RIGHT) {
				snakePtr->snakeDirection = Direction::DOWN;
				snakePtr->snakeBody.front()->velocity.x = 0;
				snakePtr->snakeBody.front()->velocity.y = 1;
				snakePtr->snakeBody.front()->setTexture("assets/snake_head_down.png");
				snakePtr->snakeBody.front()->flipTexture = SDL_FLIP_NONE;
				std::cout << "DOWN" << std::endl;
			}
			break;
		case SDLK_d:
			if (snakePtr->snakeDirection == Direction::UP || snakePtr->snakeDirection == Direction::DOWN) {
				snakePtr->snakeDirection = Direction::RIGHT;
				
				snakePtr->snakeBody.front()->velocity.x = 1;
				snakePtr->snakeBody.front()->velocity.y = 0;
				snakePtr->snakeBody.front()->setTexture("assets/snake_head_right.png");
				snakePtr->snakeBody.front()->flipTexture = SDL_FLIP_NONE;
				std::cout << "RIGHT" << std::endl;
			}
			break;
		}
	}


}
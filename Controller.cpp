#include "Controller.h"


Controller::Controller(std::shared_ptr<Snake> snake)
{
	snakePtr = snake;
}

void Controller::update()
{
	if (Game::event.type == SDL_KEYDOWN)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_w:
			if (snakePtr->getDirection() == Direction::LEFT || snakePtr->getDirection() == Direction::RIGHT) {
				snakePtr->setDirection(Direction::UP);
			}		
			break;
		case SDLK_a:
			if (snakePtr->getDirection() == Direction::UP || snakePtr->getDirection() == Direction::DOWN) {
				snakePtr->setDirection(Direction::LEFT);
			}
			break;
		case SDLK_s:
			if (snakePtr->getDirection() == Direction::LEFT || snakePtr->getDirection() == Direction::RIGHT) {
				snakePtr->setDirection(Direction::DOWN);
			}
			break;
		case SDLK_d:
			if (snakePtr->getDirection() == Direction::UP || snakePtr->getDirection() == Direction::DOWN) {
				snakePtr->setDirection(Direction::RIGHT);
			}
			
			break;

		}
	}
}
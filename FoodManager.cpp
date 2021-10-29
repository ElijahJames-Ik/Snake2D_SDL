#include "FoodManager.h"
#include "Collision.h"
#include<random>

const int foodWidth = 16;
const int foodHeight = 16;

FoodManager::FoodManager(int width, int height, std::shared_ptr<Snake> snake)
{
	food = std::make_unique<SnakeFood>("assets/snake_food.png",0,0, foodWidth, foodHeight);
	this->width = width;
	this->height = height;
	this->snake = snake;
}

void FoodManager::generateFood()
{
	if (food->isFoodEaten)
	{
			std::uniform_int_distribution<int> widthDistributor(0, width - foodWidth);
			std::uniform_int_distribution<int> heightDistributor(0, height - foodHeight);

			std::random_device rd;
			std::mt19937 randEng(rd());

			while (true)
			{
					int positionX = widthDistributor(randEng);
					int positionY = heightDistributor(randEng);
					//Check if new food location colliders snake body
					SDL_Rect newPosition;
					newPosition.x = positionX;
					newPosition.y = positionY;
					newPosition.w = food->width;
					newPosition.h = food->height;
					bool collision = false;
					for (auto itr = snake->snakeBody.begin(); itr != snake->snakeBody.end(); itr++)
					{
						if (Collision::AABB((*itr)->destRect, newPosition) == true)
						{
							collision = true;
							break;
						}
					}

					if (collision)
					{
						continue;
					}

					std::cout << "Food position X: " << positionX << std::endl;
					std::cout << "Food position Y: " << positionY << std::endl;
 			
					food->position.x = positionX;
					food->position.y = positionY;
					food->isFoodEaten = false;
					food->update();
					break;
			}
			
			
	}
}

void FoodManager::update()
{
	//check for collision
	if (Collision::AABB(snake->snakeBody.front()->destRect, food->destRect) == true)
	{
		food->isFoodEaten = true;
		snake->growSnake();
	}
	generateFood();

	
}

void FoodManager::render()
{
	food->render();
}
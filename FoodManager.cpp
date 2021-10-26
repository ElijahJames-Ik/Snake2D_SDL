#include "FoodManager.h"
#include "Collision.h"
#include<random>

FoodManager::FoodManager(int width, int height, std::shared_ptr<Snake> snake)
{
	food = std::make_unique<SnakeFood>("assets/snake_food.png",0,0,16,16);
	this->width = width;
	this->height = height;
	this->snake = snake;
}

void FoodManager::generateFood()
{
	if (food->isFoodEaten)
	{
			std::uniform_int_distribution<int> widthDistributor(0, width);
			std::uniform_int_distribution<int> heightDistributor(0, height);

			std::random_device rd;
			std::mt19937 randEng(rd());

			int positionX = widthDistributor(randEng);
			int positionY = heightDistributor(randEng);

			std::cout << "Food position X: " << positionX << std::endl;
			std::cout << "Food position Y: " << positionY << std::endl;
 			
			food->position.x = positionX;
			food->position.y = positionY;
			food->isFoodEaten = false;
			food->update();
			
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
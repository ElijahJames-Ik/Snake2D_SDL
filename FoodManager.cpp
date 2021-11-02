#include "FoodManager.h"
#include "Collision.h"
#include<random>

const int foodWidth = 16;
const int foodHeight = 16;

const int bonusWidth = 20;
const int bonusHeight = 20;


FoodManager::FoodManager(int width, int height, std::shared_ptr<Snake> snake)
{
	food = std::make_unique<SnakeFood>("assets/snake_food.png",0,0, foodWidth, foodHeight);
	bonus = std::make_unique<BonusFood>("assets/bonusFood.png", 0, 0, bonusWidth, bonusHeight);
	this->width = width;
	this->height = height;
	this->snake = snake;
}

FoodManager::~FoodManager()
{
	if (timerThread.joinable())
	{
		timerThread.join();
	}
	
}

void FoodManager::generate(std::unique_ptr<SnakeFood>& foodPtr,int foodWidth, int foodHeight )
{
	if (foodPtr->isFoodEaten)
	{
		std::uniform_int_distribution<int> widthDistributor(0, width - (foodPtr != nullptr ? foodWidth : bonusWidth));
		std::uniform_int_distribution<int> heightDistributor(0, height - (foodPtr != nullptr ? foodHeight : bonusHeight));

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
			newPosition.w =  foodPtr->width;
			newPosition.h =  foodPtr->height;
			bool collision = false;
			for (auto itr = snake->snakeBody.begin(); itr != snake->snakeBody.end(); itr++)
			{
				if (Collision::AABB((*itr)->destRect, newPosition) == true)
				{
					collision = true;
					break;
				}
			}
			if (foodPtr->isAnimated)
			{
				if (Collision::AABB(foodPtr->destRect, food->destRect))
				{
					collision = true;
				}
			}

			if (collision)
			{
				continue;
			}
	
			foodPtr->position.x = positionX;
			foodPtr->position.y = positionY;
			foodPtr->isFoodEaten = false;
			foodPtr->update();
			
			break;
		}


	}
}

void FoodManager::generateFood()
{
	
	generate(food, foodWidth, foodHeight);
}

void FoodManager::generateBonus()
{
	if (timerThread.joinable())
	{
		timerThread.join();
	}
	generate(bonus, bonusWidth, bonusHeight);

	timerThread = std::thread([this]() {
		//wait for 5 seconds before removing bonus
		std::this_thread::sleep_for(std::chrono::seconds(5));
		
			isBonusVisible = false;
		});
}



void FoodManager::update()
{
	//check for collision
	if (Collision::AABB(snake->snakeBody.front()->destRect, food->destRect) == true)
	{
		food->isFoodEaten = true;
		snake->growSnake();
		currentCount++;
		std::cout << "Snake Food Eaten" << std::endl;
	}
	if (Collision::AABB(snake->snakeBody.front()->destRect, bonus->destRect) == true && isBonusVisible)
	{
		bonus->isFoodEaten = true;
		isBonusVisible = false;
		snake->addBonus(50);
		std::cout << "Bonus Eaten" << std::endl;
	}
	if (currentCount == bonusReqCount)
	{
		std::cout << "Bonus requirement met" << std::endl;
		isBonusVisible = true;
		currentCount = 0;
		generateBonus();
	}
	if (food->isFoodEaten)
	{
		generateFood();
	}
	if (isBonusVisible)
	{
		bonus->update();
	}
	
}

void FoodManager::render()
{
	food->render();
	if (isBonusVisible)
	{
		bonus->render();
	}
	
}
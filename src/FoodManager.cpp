#include "FoodManager.h"
#include "Collision.h"
#include <random>




FoodManager::FoodManager(int width, int height, std::shared_ptr<Snake> snake)
{
	food = std::make_unique<SnakeFood>(GlobalData::snakeFoodTexture.c_str(),0,0, GlobalData::foodWidth, GlobalData::foodHeight);
	bonus = std::make_unique<BonusFood>(GlobalData::snakeBonusFoodTexture.c_str(), 0, 0, GlobalData::bonusWidth, GlobalData::bonusHeight);
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

void FoodManager::resetManager()
{
	isBonusVisible = false;
	food->isFoodEaten = true;
	bonus->isFoodEaten = true;
}

// generate snake food
void FoodManager::generate(std::unique_ptr<SnakeFood>& foodPtr,int foodWidth, int foodHeight )
{
	if (foodPtr->isFoodEaten)
	{
		std::uniform_int_distribution<int> widthDistributor((GlobalData::currentGameMap == MapType::BOXED_IN ? GlobalData::tileWidth : 0), (width - (GlobalData::currentGameMap == MapType::BOXED_IN ? GlobalData::tileWidth : 0)) - (foodPtr != nullptr ? foodWidth : GlobalData::bonusWidth));
		std::uniform_int_distribution<int> heightDistributor((GlobalData::currentGameMap == MapType::BOXED_IN ? GlobalData::tileHeight : 0), (height - (GlobalData::currentGameMap == MapType::BOXED_IN ? GlobalData::tileHeight : 0))- (foodPtr != nullptr ? foodHeight : GlobalData::bonusHeight));
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
				// check if new food location collides with snake body
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

// generate snake food
void FoodManager::generateFood()
{
	generate(food, GlobalData::foodWidth, GlobalData::foodHeight);
}

// generate snake bonus food
void FoodManager::generateBonus()
{
	if (timerThread.joinable())
	{
		timerThread.join();
	}
	generate(bonus, GlobalData::bonusWidth, GlobalData::bonusHeight);

	timerThread = std::thread([this]() {
		//wait for 5 seconds before removing bonus
		std::this_thread::sleep_for(std::chrono::seconds(5));
		
			isBonusVisible = false;
		});
}



void FoodManager::update()
{
	//check if snake head collides with snake food.
	if (Collision::AABB(snake->snakeBody.front()->destRect, food->destRect) == true)
	{
		food->isFoodEaten = true;
		snake->growSnake();
		currentCount++;
		std::cout << "Snake Food Eaten" << std::endl;
	}
	// check if snake head collides with snake bonus when it's visible
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
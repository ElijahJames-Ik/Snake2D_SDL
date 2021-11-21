#include "FoodManager.h"
#include "Collision.h"
#include "GlobalData.h"
#include<random>




FoodManager::FoodManager(int width, int height, std::shared_ptr<Snake> snake): width(width),height(height),snake(snake)
{
	food = std::make_unique<SnakeFood>(GlobalData::snakeFoodTexture.c_str(),0,0, GlobalData::foodWidth, GlobalData::foodHeight);
	bonus = std::make_unique<BonusFood>(GlobalData::snakeBonusFoodTexture.c_str(), 0, 0, GlobalData::bonusWidth, GlobalData::bonusHeight);
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
	food->setFoodState(true);
	bonus->setFoodState(true);
}

// generate snake food
void FoodManager::generate(std::unique_ptr<SnakeFood>& foodPtr,int foodWidth, int foodHeight )
{
	if (foodPtr->getFoodState())
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
			newPosition.w =  foodPtr->getWidth();
			newPosition.h =  foodPtr->getHeight();
			bool collision = false;
			// check if new food location collides with snake body.
			if (snake->checkIfFoodNewLocationCollidesWithSnakeBody(newPosition))
			{
				collision = true;
			}
			if (foodPtr->getAnimationState())
			{
				if (Collision::CheckForCollision(foodPtr->getDestRect(), food->getDestRect()))
				{
					collision = true;
				}
			}

			if (collision)
			{
				continue;
			}
	
			foodPtr->getPosition().x = positionX;
			foodPtr->getPosition().y = positionY;
			foodPtr->setFoodState(false);
			foodPtr->update();
			
			break;
		}


	}
}

// generate snake food
void FoodManager::generateFood()
{
	generate(food, GlobalData::foodWidth, GlobalData::foodHeight);
	bonusTimer(1);
}

// generate snake bonus food
void FoodManager::generateBonus()
{
	
	generate(bonus, GlobalData::bonusWidth, GlobalData::bonusHeight);

	

	//timerThread = std::thread([this]() {
	//	//wait for 5 seconds before removing bonus
	//	std::this_thread::sleep_for(std::chrono::seconds(5));
	//	
	//		isBonusVisible = false;
	//	});
}


// bonus timer
void FoodManager::bonusTimer(unsigned int interval)
{
	if (timerThread.joinable())
	{
		timerThread.detach();
	}
	timerThread =	std::thread([interval,this]() {
			while (isBonusVisible)
			{
				if (bonusSeconds == 5)
				{
					isBonusVisible = false;
					bonusSeconds = 0;
					break;
				}
				else
				{
					if (!snake->getGamePausedState())
					{
						bonusSeconds++;
					}
				}
				std::this_thread::sleep_for(std::chrono::seconds(interval));
				std::cout << bonusSeconds << std::endl;
			}
		
		});
}


void FoodManager::update()
{
	//check if snake head collides with snake food.
	if (snake->checkIfSnakeFoodIsEaten(food))
	{
		currentCount++;
	}
	// check if snake head collides with snake bonus when it's visible
	if (isBonusVisible)
	{
		if (snake->checkIfBonusFoodIsEaten(bonus))
		{
			timerThread.detach();
			isBonusVisible = false;
		}
	}
	if (currentCount == bonusReqCount)
	{
		std::cout << "Bonus requirement met" << std::endl;
		isBonusVisible = true;
		currentCount = 0;
		generateBonus();
	}
	if (food->getFoodState())
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
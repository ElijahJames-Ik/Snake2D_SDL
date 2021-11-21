#include "SnakeFood.h"
#include <random>

SnakeFood::SnakeFood(const char* textureSheet, int x, int y, int width, int height) : Actor(textureSheet, x, y, width, height)
{

}
SnakeFood::~SnakeFood()
{
	
}

void SnakeFood::update()
{
	setDestRectX( getPosition().x);
	setDestRectY(getPosition().y);
}

bool SnakeFood::getFoodState()
{
	return isFoodEaten;
}

void SnakeFood::setFoodState(bool state)
{
	isFoodEaten = state;
}


void SnakeFood::render() 
{
	TextureManager::render(getActorTexture(), getDestRect(), getFlipTexture());
}
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
	destRect.x = position.x;
	destRect.y = position.y;
}
void SnakeFood::render() 
{
	TextureManager::render(actorTexture, srcRect, destRect, flipTexture);
}
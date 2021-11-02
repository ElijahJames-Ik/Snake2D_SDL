#include "BonusFood.h"

BonusFood::BonusFood(const char* textureSheet, int x, int y, int width, int height) : SnakeFood(textureSheet, x, y, width, height)
{
	
	this->frames = 4;
	this->animationSpeed = 100;

}

void BonusFood::update()
{
	// animate bonus food sprite
	srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % frames);
	srcRect.y = 0;
	destRect.x = position.x;
	destRect.y = position.y;
}
void BonusFood::render()
{
	TextureManager::render(actorTexture,srcRect, destRect, flipTexture);
}
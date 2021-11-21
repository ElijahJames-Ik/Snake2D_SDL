#include "BonusFood.h"

BonusFood::BonusFood(const char* textureSheet, int x, int y, int width, int height) : SnakeFood(textureSheet, x, y, width, height)
{
	
	this->setAnimationsFrames (4);
	this->setAnimationSpeed(100);

}



void BonusFood::update()
{
	// animate bonus food sprite
	setSrcRectX(getWidth() * static_cast<int>((SDL_GetTicks() / getAnimationSpeed()) % getAnimationFrames()));
	setSrcRectY(0);
	setDestRectX(getPosition().x);
	setDestRectY(getPosition().y);
}
void BonusFood::render()
{
	TextureManager::render(getActorTexture(), getSrcRect(), getDestRect(), getFlipTexture());
}
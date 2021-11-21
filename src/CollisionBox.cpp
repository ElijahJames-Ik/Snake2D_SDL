#include "CollisionBox.h"

CollisionBox::CollisionBox(SDL_Rect& destRect)
{
	this->destRect = destRect;
}

SDL_Rect& CollisionBox::getDestRect()
{
	return destRect;
}

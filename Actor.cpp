#include "Actor.h"

Actor::Actor(const char* textureSheet, int x, int y, int width, int height) {
	actorTexture = TextureManager::loadTexture(textureSheet);
	flipTexture = SDL_FLIP_NONE;
	velocity.x = 1;
	velocity.y = 0;
	srcRect.h = width;
	srcRect.w = height;
	srcRect.x = 0;
	srcRect.y = 0;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

	position.x = x;
	position.y = y;
	
}

Actor::~Actor()
{
	SDL_DestroyTexture(actorTexture);
}


void Actor::setTexture(const char* filePath)
{
	actorTexture = TextureManager::loadTexture(filePath);
}
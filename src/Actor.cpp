#include "Actor.h"

Actor::Actor(const char* textureSheet, int x, int y, int width, int height) {
	
	initActor(textureSheet, x, y, width, height, false,0,0);
}

Actor::Actor(const char* textureSheet, int x, int y, int width, int height, bool animated, int frames, int speed)
{
	initActor(textureSheet, x, y, width, height, animated, frames,speed);
}

void Actor::initActor(const char* textureSheet, int x, int y, int width, int height, bool animated, int frames, int animationSpeed)
{
	actorTexture = TextureManager::loadTexture(textureSheet);
	flipTexture = SDL_FLIP_NONE;
	velocity.x = 1;
	velocity.y = 0;
	srcRect.h = height;
	srcRect.w = width;
	srcRect.x = 0;
	srcRect.y = 0;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
	destRect.x = x;
	destRect.y = y;
	position.x = x;
	position.y = y;
	this->width = width;
	this->height = height;
	this->frames = frames;
	this->animationSpeed = animationSpeed;
	isAnimated = animated;
	
}

Actor::~Actor()
{
	SDL_DestroyTexture(actorTexture);
}


void Actor::setTexture(const char* filePath)
{
	if (actorTexture != NULL)
	{
		SDL_DestroyTexture(actorTexture);
	}
	actorTexture = TextureManager::loadTexture(filePath);
}
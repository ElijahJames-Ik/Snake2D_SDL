#include "Actor.h"

Actor::Actor(const char* textureSheet, int x, int y, int width, int height) {
	
	initActor(textureSheet, x, y, width, height, false,0,0);
}

Actor::Actor(const char* textureSheet, int x, int y, int width, int height, bool animated, int frames, int speed)
{
	initActor(textureSheet, x, y, width, height, animated, frames,speed);
}
// initialize actor object
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

// set actor tecture using texture file
void Actor::setTexture(const char* filePath)
{
	if (actorTexture != NULL)
	{
		SDL_DestroyTexture(actorTexture);
	}
	actorTexture = TextureManager::loadTexture(filePath);
}
// get actor position vector
Vector2D& Actor::getPosition()
{
	return position;
}
// set actor position vector
void Actor::setPosition(Vector2D& newPosition)
{
	position = newPosition;
}
// get actor velocity vector
Vector2D& Actor::getVelocity()
{
	return velocity;
}
// set actor velocity vector
void Actor::setVelocity(Vector2D&& newVelocity)
{
	velocity = newVelocity;
}
void Actor::setVelocity(Vector2D& newVelocity)
{
	velocity = newVelocity;
}
// get actor movement speed
int Actor::getSpeed()
{
	return speed;
}
// set actor movement speed
void Actor::setSpeed(int speed)
{
	this->speed = speed;
}
// get actor render flip object
SDL_RendererFlip Actor::getFlipTexture()
{
	return flipTexture;
}
// set actor render flip object
void Actor::setFlipTexture(SDL_RendererFlip& sdlFlip)
{
	flipTexture = sdlFlip;
}
// get actor texture
SDL_Texture* Actor::getActorTexture()
{
	return actorTexture;
}
// set actor texture using sdl texture object
void Actor::setActorTexture(SDL_Texture* texture)
{
	auto tmp = actorTexture;
	actorTexture = texture;
	SDL_DestroyTexture(tmp);
	
}
// get source rectangle
SDL_Rect& Actor::getSrcRect()
{
	return srcRect;
}
// set source rectangle
void Actor::setSrcRect(SDL_Rect& rect)
{
	srcRect = rect;
}
// get destination rectangle
SDL_Rect& Actor::getDestRect()
{
	return destRect;
}
// set destination rectangle
void Actor::setDestRect(SDL_Rect& rect)
{
	destRect = rect;
}
// get actor object width
int Actor::getWidth()
{
	return width;
}
// set actor object width
void Actor::setWidth(int width)
{
	this->width = width;
}
// get actor object height
int Actor::getHeight()
{
	return height;
}
// set actor object height
void Actor::setHeight(int height)
{
	this->height = height;
}
// get actor object animated state
bool Actor::getAnimationState()
{
	return isAnimated;
}
// set actor object animated state
void Actor::setAnimationState(bool state)
{
	this->isAnimated = state;
}
// get actor object animation frames
int Actor::getAnimationFrames()
{
	return frames;
}
// set actor object animation frames
void Actor::setAnimationsFrames(int frames)
{
	this->frames = frames;
}
// get actor object animation speed
int Actor::getAnimationSpeed()
{
	return animationSpeed;
}
// set actor object animation speed
void Actor::setAnimationSpeed(int speed)
{
	animationSpeed = speed;
}
// set source rectangle x coordinate value
void Actor::setSrcRectX(int x)
{
	srcRect.x = x;
}
// set source rectanle  y coordinate value
void Actor::setSrcRectY(int y)
{
	srcRect.y = y;
}
// set source rectangle width value
void  Actor::setSrcRectW(int w)
{
	srcRect.w = w;
}
// set source rectangle height value
void Actor::setSrcRectH(int h)
{
	srcRect.h = h;
}
// set destination rectangle x coordinate value
void Actor::setDestRectX(int x)
{
	destRect.x = x;
}
// set destination rectangle y coordinate value
void Actor::setDestRectY(int y)
{
	destRect.y = y;
}
// set destination rectangle width value
void Actor::setDestRectW(int w)
{
	destRect.w = w;
}
// set destination rectangle height value
void Actor::setDestRectH(int h)
{
	destRect.h = h;
}
// set position vector x coordinate value
void Actor::setPositionX(int x)
{
	position.x = x;
}
// set position vector y coordinate value
void Actor::setPositionY(int y)
{
	position.y = y;
}
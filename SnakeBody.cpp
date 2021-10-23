#include "SnakeBody.h"


SnakeBody::SnakeBody(const char* textureSheet, int x, int y) : Actor(textureSheet,x,y) 
{
	velocity.x = 1;
	velocity.y = 0;
	srcRect.h = 8;
	srcRect.w = 8;
	srcRect.x = 0;
	srcRect.y = 0;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}
SnakeBody::~SnakeBody()
{

}

void SnakeBody::update()
{
	position.x += velocity.x * speed;
	position.y += velocity.y * speed;
	if (position.x > 800)
	{
		position.x = 0;
	}

	

	destRect.x = position.x;
	destRect.y = position.y;
	
}
void SnakeBody::render() {
	SDL_RenderCopy(Game::renderer, actorTexture, &srcRect, &destRect);
}
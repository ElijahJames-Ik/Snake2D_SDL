#include "SnakeBody.h"


SnakeBody::SnakeBody(const char* textureSheet, int x, int y) : Actor(textureSheet,x,y) 
{
	
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
	if (position.x < 0)
	{
		position.x = 800;
	}
	if (position.y > 640)
	{
		position.y = 0;
	}
	if (position.y < 0)
	{
		position.y = 640;
	}

	

	destRect.x = position.x;
	destRect.y = position.y;
	
}
void SnakeBody::render() {
	SDL_RenderCopy(Game::renderer, actorTexture, &srcRect, &destRect);
}
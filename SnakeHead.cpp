#include "SnakeHead.h"


SnakeHead::SnakeHead(const char* textureSheet, int x, int y) : Actor(textureSheet, x, y)
{
	
}
SnakeHead::~SnakeHead()
{

}

void SnakeHead::update()
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
void SnakeHead::render() {
	SDL_RenderCopy(Game::renderer, actorTexture, &srcRect, &destRect);
}
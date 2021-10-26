#include "SnakeHead.h"


SnakeHead::SnakeHead(const char* textureSheet, int x, int y, int width, int height) : Actor(textureSheet, x, y, width, height)
{

}
SnakeHead::~SnakeHead()
{

}

void SnakeHead::update()
{
	position.x += velocity.x * speed;
	position.y += velocity.y * speed;
	if (position.x > Game::windowWidth)
	{
		position.x = 0;
	}
	if (position.x < 0)
	{
		position.x = Game::windowWidth;
	}
	if (position.y > Game::windowHeight)
	{
		position.y = 0;
	}
	if (position.y < 0)
	{
		position.y = Game::windowHeight;
	}
	destRect.x = position.x;
	destRect.y = position.y;
	
}
void SnakeHead::render() {
	TextureManager::draw(actorTexture, srcRect, destRect, flipTexture);
}
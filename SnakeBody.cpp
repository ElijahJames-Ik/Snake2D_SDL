#include "SnakeBody.h"
#include "Game.h"


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
void SnakeBody::render() {
	TextureManager::draw(actorTexture, srcRect, destRect, flipTexture);
}
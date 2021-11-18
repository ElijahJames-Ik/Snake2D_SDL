#include "SnakeBody.h"
#include "Game.h"
#include "GlobalData.h"


SnakeBody::SnakeBody(const char* textureSheet, int x, int y, int width, int height) : Actor(textureSheet,x,y,width,height)
{
	speed = GlobalData::snakeSpeed;
}
SnakeBody::~SnakeBody()
{

}

//update snake body part location
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
		position.x = Game::windowWidth - GlobalData::bodyWidth;
	}
	if (position.y > Game::windowHeight)
	{
		position.y = 0;
	}
	if (position.y < 0)
	{
		position.y = Game::windowHeight - GlobalData::bodyHeight;
	}



	destRect.x = position.x;
	destRect.y = position.y;

	
}
void SnakeBody::render() {
	TextureManager::render(actorTexture, destRect, flipTexture);
}

void SnakeBody::pauseMovement()
{
	pausedState = velocity;
	velocity = Vector2D();
}

void SnakeBody::resumeMovement()
{
	velocity = pausedState;
}
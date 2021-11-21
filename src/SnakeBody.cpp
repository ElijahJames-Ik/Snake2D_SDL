#include "SnakeBody.h"
#include "Game.h"
#include "GlobalData.h"


SnakeBody::SnakeBody(const char* textureSheet, int x, int y, int width, int height) : Actor(textureSheet,x,y,width,height)
{
	setSpeed(GlobalData::snakeSpeed);
}
SnakeBody::~SnakeBody()
{

}

//update snake body part location
void SnakeBody::update()
{
	setPositionX(getPosition().x + (getVelocity().x * getSpeed()));
	setPositionY(getPosition().y + (getVelocity().y * getSpeed()));

	if (getPosition().x > Game::windowWidth)
	{
		setPositionX(0);
	}
	if (getPosition().x < 0)
	{
		setPositionX(Game::windowWidth - GlobalData::bodyWidth);
	}
	if (getPosition().y > Game::windowHeight)
	{
		setPositionY(0);
	}
	if (getPosition().y < 0)
	{
		setPositionY(Game::windowHeight - GlobalData::bodyHeight);
	}
	setDestRectX(getPosition().x);
	setDestRectY(getPosition().y);
}
void SnakeBody::render() {
	auto dest = getDestRect();

	TextureManager::render(getActorTexture(), getDestRect(), getFlipTexture());
}

void SnakeBody::pauseMovement()
{
	pausedState = getVelocity();
	setVelocity(Vector2D());
}

void SnakeBody::resumeMovement()
{
	setVelocity(pausedState);
}
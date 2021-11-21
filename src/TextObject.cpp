#include "TextObject.h"
#include "TextureManager.h"
#include <iostream>


TextObject::TextObject(std::string& filePath, int fontSize, SDL_Color textColor,std::string message,int x, int y):
filePath(filePath),color(textColor),fontSize(fontSize), message(message), xPos(x),yPos(y)
{
	setText(message.c_str());
}

void TextObject::setColor(SDL_Color color)
{
	this->color = color;
	setText(message.c_str());
}

void TextObject::setText(const char* text)
{
	/*if (messageTexture != NULL)
	{
		SDL_DestroyTexture(messageTexture);
		messageTexture = NULL;
	}*/
	TTF_Init();
	TTF_Font* fontFile = TTF_OpenFont(filePath.c_str(), fontSize);



	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(fontFile, text, color);

	messageTexture = TextureManager::loadTextureFromText(surfaceMessage);
	msgRect.x = xPos;
	msgRect.y = yPos;
	msgRect.w = surfaceMessage->w;
	msgRect.h = surfaceMessage->h;
	TTF_CloseFont(fontFile);
	SDL_FreeSurface(surfaceMessage);
	TTF_Quit();
}

TextObject::~TextObject()
{
	SDL_DestroyTexture(messageTexture);
	
}

void TextObject::render()
{
	if (messageTexture != NULL)
	{
		TextureManager::render(messageTexture, msgRect);
	}
}

void TextObject::update()
{

}


int TextObject::getXPos()
{
	return xPos;
}
void TextObject::setXPos(int x)
{
	xPos = x;
}
int TextObject::getYPos()
{
	return yPos;
}
void TextObject::setYPos(int y)
{
	yPos = y;
}
int TextObject::getWidth()
{
	return width;
}
void TextObject::setWidth(int w)
{
	width = w;
}
int TextObject::getHeight()
{
	return height;
}
void TextObject::setHeight(int h)
{
	height = h;
}
int TextObject::getFontSize()
{
	return fontSize;
}
void TextObject::setFontSize(int size)
{
	fontSize = size;
}

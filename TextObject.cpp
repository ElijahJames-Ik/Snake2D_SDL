#include "TextObject.h"
#include "TextureManager.h"
#include <iostream>


TextObject::TextObject(std::string filePath, int fontSize, SDL_Color textColor,std::string message,int x, int y, int width, int height)
{
	xPos = x;
	yPos = y;
	this->width = width;
	this->height = height;
	this->filePath = filePath;
	this->color = textColor;
	this->fontSize = fontSize;
	this->message = message;
	setText(message.c_str());
}

void TextObject::setColor(SDL_Color color)
{
	this->color = color;
	setText(message.c_str());
}

void TextObject::setText(const char* text)
{
	if (messageTexture != NULL)
	{
		SDL_DestroyTexture(messageTexture);
		messageTexture = NULL;
	}
	TTF_Init();
	TTF_Font* fontFile = TTF_OpenFont(filePath.c_str(), fontSize);



	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(fontFile, text, color);

	messageTexture = TextureManager::loadTextureFromText(surfaceMessage);
	msgRect.x = xPos;
	msgRect.y = yPos;
	msgRect.w = width;
	msgRect.h = height;
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
	TextureManager::render(messageTexture, msgRect);
}

void TextObject::update()
{

}


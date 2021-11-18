#include "TextObject.h"
#include "TextureManager.h"
#include <iostream>


TextObject::TextObject(std::string& filePath, int fontSize, SDL_Color textColor,std::string message,int x, int y)
{
	xPos = x;
	yPos = y;
	
	this->filePath = filePath;
	this->color = textColor;
	this->fontSize = fontSize;
	this->message = message;
	setText(message.c_str());
	std::cout << "Text Object created" << std::endl;
}

void TextObject::setColor(SDL_Color color)
{
	this->color = color;
	setText(message.c_str());
}

void TextObject::setText(const char* text)
{
	// if (messageTexture != NULL)
	// {
	// 	SDL_DestroyTexture(messageTexture);
	// 	messageTexture = NULL;
	// }
	TTF_Init();
	TTF_Font* fontFile = TTF_OpenFont(filePath.c_str(), fontSize);
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(fontFile, text, color);
	messageTexture = TextureManager::loadTextureFromText(surfaceMessage);
	msgRect.x = xPos;
	msgRect.y = yPos;
	msgRect.w = surfaceMessage->w;
	msgRect.h = surfaceMessage->h;
	SDL_FreeSurface(surfaceMessage);
	TTF_CloseFont(fontFile);
	TTF_Quit();

}

TextObject::~TextObject()
{
	if(messageTexture != NULL)
	{
		SDL_DestroyTexture(messageTexture);
	}
	
	
}

void TextObject::render()
{
	if(messageTexture != NULL)
	{
		TextureManager::render(messageTexture, msgRect);
	}	
	
}

void TextObject::update()
{

}


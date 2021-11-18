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
	std::cout << "Creating texture" << std::endl;
	// if (messageTexture != NULL)
	// {
	// 	SDL_DestroyTexture(messageTexture);
	// 	messageTexture = NULL;
	// }
	std::cout << "Initializing TTF" << std::endl;
	TTF_Init();
	std::cout << "Done inti" << std::endl;
	TTF_Font* fontFile = TTF_OpenFont(filePath.c_str(), fontSize);
	std::cout << "Font loaded" << std::endl;



	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(fontFile, text, color);
	std::cout << "Surface created" << std::endl;
	messageTexture = TextureManager::loadTextureFromText(surfaceMessage);
	std::cout << "Texture loaded" << std::endl;
	msgRect.x = xPos;
	msgRect.y = yPos;
	msgRect.w = surfaceMessage->w;
	msgRect.h = surfaceMessage->h;
	std::cout << "Dimensions set" << std::endl;
	SDL_FreeSurface(surfaceMessage);
	std::cout << "Surface cleaned" << std::endl;
	TTF_CloseFont(fontFile);
	std::cout << "File closed" << std::endl;
	TTF_Quit();

	std::cout << "TTF existed" << std::endl;
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


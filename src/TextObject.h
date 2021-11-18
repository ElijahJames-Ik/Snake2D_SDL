#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class TextObject
{
public:
	TextObject(std::string& filePath, int fontSize, SDL_Color textColor,std::string message, int x, int y);
	~TextObject();
	void update();
	void render();
	void setText(const char* text);
	void setColor(SDL_Color color);
	int xPos;
	int yPos;
	int width;
	int height;
	int fontSize;
private:
	SDL_Texture* messageTexture;
	SDL_Rect msgRect;
	
	std::string filePath;
	SDL_Color color;
	std::string message;

};
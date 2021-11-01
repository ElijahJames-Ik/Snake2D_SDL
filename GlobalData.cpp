#include "GlobalData.h"

SDL_Color GlobalData::white = { 255,255,255 };

SDL_Color GlobalData::red = { 255,0,0 };

int GlobalData::currentMenuSelection = 1;

bool GlobalData::menuOptionChanged = false;

GamePage GlobalData::currentPage = GamePage::HOME;

std::string GlobalData::menuItemTextFont = "assets/Bullpen3D.ttf";

std::string GlobalData::titleTextFont = "assets/StitchWarrior.ttf";
#include "GlobalData.h"

SDL_Color GlobalData::white = { 255,255,255 };

SDL_Color GlobalData::red = { 255,0,0 };

SDL_Color GlobalData::green = { 0,255,0 };

int GlobalData::currentMenuSelection = 1;

int GlobalData::tileHeight = 32;

int GlobalData::tileWidth = 32;

int GlobalData::snakeSpeed = GlobalData::normalSpeed;

bool GlobalData::menuOptionChanged = false;
bool GlobalData::settingsChanged = false;
bool GlobalData::isDataLoadRequired = true;
bool GlobalData::isControllerLocked = false;


GamePage GlobalData::currentPage = GamePage::HOME;

MapType GlobalData::currentGameMap = MapType::BOXED_IN;
GameDifficult GlobalData::gameDifficulty = GameDifficult::NORMAL;

std::string GlobalData::menuItemTextFont = "assets/Bullpen3D.ttf";

std::string GlobalData::titleTextFont = "assets/StitchWarrior.ttf";

std::string GlobalData::snakeBodyTexture = "assets/snake_cube.png";

std::string GlobalData::snakeHeadUpTexture = "assets/snake_head_up.png";
std::string GlobalData::snakeHeadDownTexture = "assets/snake_head_down.png";
std::string GlobalData::snakeHeadLeftTexture = "assets/snake_head_left.png";
std::string GlobalData::snakeHeadRightTexture = "assets/snake_head_right.png";
std::string GlobalData::snakeFoodTexture = "assets/snake_food.png";
std::string GlobalData::snakeBonusFoodTexture = "assets/bonusFood.png";

std::string GlobalData::highscoreFile = "data/highscore.txt";
std::string GlobalData::gameSettingsFile = "data/gameSettings.txt";

std::string GlobalData::openFieldTexture = "assets/no_barrier_map_texture.png";
std::string GlobalData::openFileMapFile = "assets/defaultMap.map";
std::string GlobalData::boxedInFieldTexture = "assets/collision_snake_map_texture.png";
std::string GlobalData::boxedInFileMapFile = "assets/collisionMap.map";

std::string GlobalData::tileMapFile = boxedInFileMapFile;
std::string GlobalData::worldMapTexture = boxedInFieldTexture;



#pragma once
#include<string>
#include<vector>
#include<memory>
#include"Tile.h"
#include "CollisionBox.h"
#include <thread>

class WorldMap
{
public:
	WorldMap();
	~WorldMap();
	void render();
	void LoadWorldMap(std::string& filePath, int tilesX, int tilesY);
	std::vector<std::unique_ptr<CollisionBox>> collisionBoxes;
private:
	std::vector<std::unique_ptr<Tile>> worldTiles;
	
};
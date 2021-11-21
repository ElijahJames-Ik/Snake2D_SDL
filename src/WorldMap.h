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
	// Render game map
	void render();
	// Load map assets
	void LoadWorldMap(std::string& filePath, int tilesX, int tilesY);
	// get map collision locations on map
	std::vector<std::shared_ptr<CollisionBox>>& getCollisionBoxesList();
private:
	// Holds all map tiles
	std::vector<std::unique_ptr<Tile>> worldTiles;
	// Holds all map collision location
	std::vector<std::shared_ptr<CollisionBox>> collisionBoxes;
	
};
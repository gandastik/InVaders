#pragma once

#include"Tile.h"

class TileMap
{
private:
	std::vector< std::vector<Tile*> > Tiles;

public:
	TileMap();
	~TileMap();

	//Functions
	void addTile(unsigned x, unsigned y);
	void removeTile(unsigned x, unsigned y);

	void update();
	void render();
};


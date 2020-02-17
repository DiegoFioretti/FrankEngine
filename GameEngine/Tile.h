#pragma once
#include "Sprite.h"
class FRANKENGINE_API Tile:
	public Sprite

{
private:
	bool _walkable;
	int _id;
public:
	Tile(Renderer* render, int columns, int rows, int id/*,bool walkable*/);
	~Tile();
	bool isWalkable();
	void setWalkable(bool walk);
	int getTileID();
};
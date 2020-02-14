#pragma once
#include "Sprite.h"
class FRANKENGINE_API Tile:
	public Sprite

{
private:
	bool _walkable;
	
public:
	Tile(Renderer* render, int columns, int rows,bool walkable);
	~Tile();
	bool isWalkable();
	void setWalkable(bool walk);

};
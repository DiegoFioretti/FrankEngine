#include "Tile.h"

Tile::Tile(Renderer* render, int columns, int rows, bool walkable): Sprite( render,  columns, rows)
{
	_walkable = false;
}


Tile::~Tile()
{
}

bool Tile::isWalkable() {
	return _walkable;
}

void Tile::setWalkable(bool walk) {
	_walkable = walk;
}
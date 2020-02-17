#include "Tile.h"

Tile::Tile(Renderer* render, int columns, int rows, int id): Sprite( render,  columns, rows)
{
	_walkable = true;
	_id = id;
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

int Tile::getTileID()
{
	return _id;
}
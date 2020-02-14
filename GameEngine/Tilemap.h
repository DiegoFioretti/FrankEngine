#pragma once
#include "Tile.h"
class FRANKENGINE_API Tilemap
{
private:
	GLuint width;  //ancho en tiles
	GLuint height; //alto en tile
	GLuint tileWidth;//ancho del tile
	GLuint tileHeight;//alto del tile
	
public:
	Tilemap();
	~Tilemap();
};


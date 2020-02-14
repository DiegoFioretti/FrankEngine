#pragma once
#include "Tile.h"
class FRANKENGINE_API Tilemap
{
private:
	GLuint width;		//ancho de mapa en tiles
	GLuint height;		//alto de mapa en tiles
	GLuint tileWidth;	//ancho de tiles en pixeles
	GLuint tileHeight;	//alto de tiles en pixeles
	
	Tile* pasto;
	Tile* caja;
public:
	Tilemap(Renderer* render, Material* material, const char* bmpFile, int columns, int rows);
	~Tilemap();
	void DrawTiles();
};


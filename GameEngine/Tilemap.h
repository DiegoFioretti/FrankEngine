#pragma once
#include "Tile.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstring>
#define MAXTILES 20
#define MAXTILESINMAP 250

class FRANKENGINE_API Tilemap
{
private:
	GLuint _mapWidth;		//ancho de mapa en tiles
	GLuint _mapHeight;		//alto de mapa en tiles
	GLuint tileWidth;	//ancho de tiles en pixeles
	GLuint tileHeight;	//alto de tiles en pixeles

	int _x;
	int _y;
	int _z;
	bool _tilesetExist;

	//Tile* pasto;
	//Tile* caja;

	//list<Tile*>* _tileArchive;

	int _mapGuide[MAXTILESINMAP];
public:
	int _tileAmount;
	Tile* _tileArchive[MAXTILES];

	Tilemap(int x, int y, int z);
	~Tilemap();
	void loadBMPTileset(Renderer* render, Material* material, const char* bmpFile, int columns, int rows);
	void loatTXTTilemap(const char* txtFile, int width, int height);
	void DrawTiles();
	void UpdateTilesAnim(float time);
};


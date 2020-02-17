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

	float _x;
	float _y;
	float _z;
	bool _tilesetExist;

	int _tileAmount;

	Tile* _tileArchive[MAXTILES];

	int _mapGuide[MAXTILESINMAP];

	int num = 0;
public:
	Tilemap(float x, float y, float z);
	~Tilemap();
	void loadBMPTileset(Renderer* render, Material* material, const char* bmpFile, int columns, int rows);
	void loatTXTTilemap(const char* txtFile, int width, int height);
	void DrawTiles();
	void UpdateTilesAnim(float time);
	int GetTileAmount();
	Tile* GetTileInfo(int tileid);
};


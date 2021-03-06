#pragma once
#include "Tile.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <iostream>

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
	bool first = true;
	vector <vec3> pos;

	int _tileAmount=0;
	Tile* auxTile;
	CollisionManager* cul;
	vector <Tile*> _tileArchive;
	vector <Tile*> totalTiles;
	Tile* test;
	vector<float*>* uvVector;
	float* uvArrays;
	int _mapGuide[MAXTILESINMAP];

	int num = 0;
public:
	Tilemap(float x, float y, float z);
	~Tilemap();
	void loadBMPTileset( Material* material, const char* bmpFile, int columns, int rows);
	void loatTXTTilemap(const char* txtFile, int width, int height);
	void DrawTiles();
	int GetTileAmount();
	void CutTileSet(int col, int row);
	float* GetTile(int index);
	Tile* GetTileInfo(int tileid);
	void MakeColTile(Entity* A, int numTile);

};


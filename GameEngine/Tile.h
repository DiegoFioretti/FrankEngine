#pragma once
#include "CollisionManager.h"
#include "Shape.h"
#include "TextureImporter.h"

class FRANKENGINE_API Tile : public Shape
{
private:
	bool _walkable;
	int _id;
	float _x;
	float _y;
	float _z;
	BMPheader texture;
	float* uvArray;
	unsigned int uvBufferID=0;
	unsigned int textureID=0;
	int uvVtxCount;
	bool ShouldDispouseTexture;

public:
	Tile(float x, float y, float z, int id, bool walk);
	~Tile();
	void Draw() override;
	void DrawMeshWithTexture(int typeDraw);
	void LoadTexture(const char* bmpFile);
	void SetTextureVertex(float* vertices, int count);
	void DisposeTexture();
	bool isWalkable();
	void setWalkable(bool walk);
	int getTileID();
};
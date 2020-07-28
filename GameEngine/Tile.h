#pragma once

#include "Shape.h"
#include "CollisionManager.h"
#include "TextureImporter.h"

class FRANKENGINE_API Tile : public Shape
{
protected:
	float* uvArray;
private:

	int _id;
	BMPheader texture;
	unsigned int uvBufferID=0;
	unsigned int textureID=0;
	int uvVtxCount;
	bool ShouldDispouseTexture;
	//CollisionManager* col;

public:
	Tile(int id);
	~Tile();
	void Draw() override;
	void DrawMeshWithTexture(int typeDraw);
	void LoadTexture(const char* bmpFile);
	void SetTextureVertex(float* vertices, int count);
	void DisposeTexture();
	bool isWalkable();
	void setWalkable(bool walk);
	void UVArr(float * uv);
	int getTileID();
	void TileCol();
};
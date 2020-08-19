#pragma once
#include "Exports.h"
#include "Shape.h"
#include "TextureImporter.h"
#include "Animation.h"

class FRANKENGINE_API Sprite : public Shape
{
private:

	BMPheader texture;
	float * uvArray;
	unsigned int uvBufferID;
	unsigned int textureID;
	int uvVtxCount;
	Animation * anim;
	bool onCollision;
	bool ShouldDispouseTexture;

	bool ShouldDispouseTexture;
	int animB;
	int animE;

public:
	void Draw() override;
	void DrawMeshWithTexture(int typeDraw);
	void LoadTexture(const char * bmpFile);
	void SetTextureVertex(float * vertices, int count);

	void UpdAnim(float deltaTime);
	void SetAnim(int initF, int finishF, float timePerF);

	void DisposeTexture();

	void setCollision();
	bool getCollision();


	Sprite(int columns, int rows);
	~Sprite();
};


#pragma once
#include "Exports.h"
#include "Shape.h"
#include "TextureImporter.h"
#include "Animation.h"
class FRANKENGINE_API Sprite :
	public Shape
{
private:

	BMPheader texture;
	float * uvArray;
	unsigned int uvBufferID;
	unsigned int textureID;
	int uvVtxCount;
	Animation * anim;

	bool onCollision;
public:
	void Draw() override;
	void DrawMeshWithTexture(int typeDraw);
	void LoadMaterial(const char * bmpFile);
	void SetTextureVertex(float * vertices, int count);

	void UpdAnim(float deltaTime);
	void SetAnim(int initF, int finishF, float timePerF);

	void setCollision();
	bool getCollision();

	Sprite(Renderer * render, int columns, int rows);
	~Sprite();
};


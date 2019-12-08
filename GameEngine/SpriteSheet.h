#pragma once
#include "Exports.h"
#include <vector>
using namespace std;

class FRANKENGINE_API SpriteSheet
{
private:
	float *uvArrays;
	vector<float*> * uvVector;
	int textureH;
	int textureW;

public:
	SpriteSheet(int columns, int rows, int texW,int texH);
	~SpriteSheet();
	float* GetSprite(int index);
	int GetSize();
};
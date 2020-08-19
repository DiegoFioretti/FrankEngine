#pragma once
#include "Exports.h"
#include <vector>
using namespace std;

class FRANKENGINE_API SpriteSheet
{
private:
	float *uvArrays;
	vector<float*> * uvVector;


public:
	SpriteSheet(int columns, int rows);
	~SpriteSheet();
	float* GetSprite(int index);
	int GetSize();
};
#include "SpriteSheet.h"

// divide la imagen por las columnas y filas
SpriteSheet::SpriteSheet(int columns, int rows) 
{
	uvVector = new vector<float*>();
	float frameW = 1.0f / columns;
	float frameH = 1.0f / rows;
	int totalSprites = columns * rows;

	for (int i = 0; i < totalSprites; i++) {
		float x = (i % columns) * frameW;
		float y = (i / columns) * frameH;

		uvArrays = new float[8]
		{
			 x , 1 - (y + frameH),
			 x , 1 - y ,
			(x + frameW) , 1 - (y + frameH),
			(x + frameW) , 1 - (y)
		};

		uvVector->push_back(uvArrays);
	}
}

SpriteSheet::~SpriteSheet()
{
	delete uvVector;
}

float* SpriteSheet::GetSprite(int index)
{
	return uvVector->at(index);
}

int SpriteSheet::GetSize()
{
	return uvVector->size();
}
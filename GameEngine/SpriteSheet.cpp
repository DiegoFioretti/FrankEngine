#include "SpriteSheet.h"

// divide la imagen por las columnas y filas
SpriteSheet::SpriteSheet(int columns, int rows) 
{
	uvVector = new vector<float*>();
	float frameW = 1.0f / columns;
	float frameH = 1.0f / rows;
	int totalSprites = columns * rows;

	for (int i = 0; i < totalSprites; i++) {
		//Este calculo hace un recorrido sobre los sprites
		float x = (i % columns) * frameW; //Este va a la derecha
		float y = (i / columns) * frameH; //Este baja 

		// aca van los puntos de cada sprite
		uvArrays = new float[8]
		{
			 x , 1 - (y + frameH),			//minX y minY
			 x , 1 - y ,					//minX y maxY 
			(x + frameW) , 1 - (y + frameH),//maxX y minY
			(x + frameW) , 1 - (y)			//maxX y maxY
		};

		uvVector->push_back(uvArrays);
	}
	int i;
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
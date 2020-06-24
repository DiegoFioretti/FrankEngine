#include "Animation.h"

//Le pasas las columnas y filas de la animacion
Animation::Animation(int columns, int rows) {
	sprSheet = new SpriteSheet(columns, rows, 1, 1);
	initialFrame = 0;
	lastFrame = 0;
	timePerFrame = 0.0f;
	currentTime = 0.0f;
	currentFrame = 0;
}

Animation::~Animation()
{
	delete sprSheet;
}
//Se le pasa que frames se quieren pasar y en cuanto tiempo
void Animation::SetAnimation(int initF, int finalF, float timePerF)
{
	if (initF >= 0 && finalF < sprSheet->GetSize() && timePerF > 0)
	{
		initialFrame = initF;
		lastFrame = finalF;
		timePerFrame = timePerF;
		currentTime = 0.0f;
		currentFrame = initialFrame;
	}
}
//Le pasas el delta time para pasar la animacion ...ponele
float * Animation::UpdateAnimation(float deltaTime)
{
	currentTime += deltaTime;
	if (currentTime >= timePerFrame)
	{
		currentTime = timePerFrame - currentTime;

		if (currentFrame < lastFrame)
		{
			currentFrame++;
		}
		else
		{
			currentFrame = initialFrame;
		}		
	}

	return sprSheet->GetSprite(currentFrame);
}
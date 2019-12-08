#pragma once
#include "Exports.h"
#include "SpriteSheet.h"

class FRANKENGINE_API Animation
{
private:
	SpriteSheet* sprSheet;
	int initialFrame;
	int currentFrame;
	int lastFrame;

	float timePerFrame;
	float currentTime;

public:
	Animation(int column, int rows);
	~Animation();
	void SetAnimation(int initF, int finalF, float timePerF);
	float * UpdateAnimation(float deltaTime);
};

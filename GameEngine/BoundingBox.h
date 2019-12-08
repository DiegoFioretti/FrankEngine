#pragma once
#include "Exports.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;
using namespace glm;

class FRANKENGINE_API BoundingBox
{
private:
	vec2 boxPosition;
	float height;
	float width;
	bool collision;

public:
	BoundingBox(vec2 pos, unsigned int width, unsigned int heigth);
	~BoundingBox();
	float GetX();
	float GetY();
	vec2 GetPos();
	void SetPos(float x, float y);
	float GetWidth();
	float GetHeigth();
	bool GetCollision();
	void SetCollision(bool value);
};
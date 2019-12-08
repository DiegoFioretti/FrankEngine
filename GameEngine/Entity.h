#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "BoundingBox.h"

#include<iostream>
using namespace std;
using namespace glm;
class FRANKENGINE_API Entity
{
private:
	vec3 pos;
	vec3 rot;
	vec3 scale;

protected:
	Renderer* render;
	mat4 WorldMatrix;
	mat4 TranslateMatrix;
	mat4 RotMatrix;
	mat4 ScaleMatrix;
	void UpdateWorldMatrix();
	BoundingBox *boundBox;

public:

	Entity(Renderer * renderPTR);
	virtual void Draw() = 0;
	void SetPos(float x, float y, float z);
	void SetRot(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void Translate(float x, float y, float z);
	void Rotate(float x, float y, float z);
	vec3 GetPos();
	vec3 GetRot();
	vec3 GetScale();

	void SetBoundingBox(float width, float heigth);
	BoundingBox* GetBoundingBox();
};


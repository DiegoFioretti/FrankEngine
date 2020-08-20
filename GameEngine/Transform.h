#pragma once
#include "Exports.h"
#include "Renderizer.h"
#include "AABB.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include<iostream>
using namespace std;
using namespace glm;





class FRANKENGINE_API Transform
{
private:
	vec3 pos;
	vec3 rot;
	vec3 scale;
protected:
	mat4 WorldMatrix;
	mat4 TranslateMatrix;
	mat4 RotMatrix;
	mat4 ScaleMatrix;
	void UpdateWorldMatrix(); 
public:
	Transform();
	void SetPos(vec3 newPos);
	void SetRot(vec3 newRot);
	void SetScale(vec3 newScale);
	void Translate(float x, float y, float z);
	void Rotate(float x, float y, float z);
	vec3 GetPos();
	vec3 GetRot();
	vec3 GetScale();
	mat4 GetWorldMatrix();
};


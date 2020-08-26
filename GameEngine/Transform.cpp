#include "Transform.h"

Transform::Transform()
{
	render = Renderizer::GetInstance()->rnd;

	WorldMatrix = mat4(1.0f);
	TranslateMatrix = mat4(1.0f);
	RotMatrix = mat4(1.0f);
	ScaleMatrix = mat4(1.0f);

	pos[0] = pos[1] = pos[2] = 0.0f;
	rot[0] = rot[1] = rot[2] = 0.0f;
	scale[0] = scale[1] = scale[2] = 1.0f;
}

void Transform::SetPos(vec3 newPos)
{
	pos = newPos;

	TranslateMatrix = translate(mat4(1.0f), pos);
	UpdateWorldMatrix();
}

void Transform::SetRot(vec3 newRot)
{
	rot = newRot;

	RotMatrix = rotate(mat4(1.0f), rot.x, vec3(1.0f, 0.0f, 0.0f));
	RotMatrix *= rotate(mat4(1.0f), rot.y, vec3(0.0f, 1.0f, 0.0f));
	RotMatrix *= rotate(mat4(1.0f), rot.z, vec3(0.0f, 0.0f, 1.0f));

	UpdateWorldMatrix();
}

void Transform::SetScale(vec3 newScale)
{
	ScaleMatrix = glm::scale(mat4(1.0f), newScale);

	UpdateWorldMatrix();
}

void Transform::UpdateWorldMatrix()
{
	WorldMatrix = TranslateMatrix * RotMatrix * ScaleMatrix;
}

vec3 Transform::GetPos()
{
	return pos;
}

vec3 Transform::GetRot()
{
	return rot;
}

vec3 Transform::GetScale()
{
	return scale;
}
mat4 Transform::GetWorldMatrix()
{
	return WorldMatrix;
}

void Transform::Translate(float x, float y, float z)
{
	pos[0] += x;
	pos[1] += y;
	pos[2] += z;

	TranslateMatrix = translate(mat4(1.0f), pos);
	UpdateWorldMatrix();
}
void Transform::Rotate(float x, float y, float z)
{
	rot[0] += x;
	rot[1] += y;
	rot[2] += z;

	RotMatrix = rotate(mat4(1.0f), rot[0], vec3(1.0f, 0.0f, 0.0f));
	RotMatrix *= rotate(mat4(1.0f), rot[1], vec3(0.0f, 1.0f, 0.0f));
	RotMatrix *= rotate(mat4(1.0f), rot[2], vec3(0.0f, 0.0f, 1.0f));

	UpdateWorldMatrix();
}

#include "Entity.h"

//Guarda todos los valores de transformacion del objeto 
Entity::Entity(Renderer *renderPTR)
{
	boundBox = NULL;
	render = renderPTR;
	WorldMatrix = mat4(1.0f);
	TranslateMatrix = mat4(1.0f);
	RotMatrix = mat4(1.0f);
	ScaleMatrix = mat4(1.0f);

	pos[0] = pos[1] = pos[2] = 0.0f;
	rot[0] = rot[1] = rot[2] = 0.0f;
	scale[0] = scale[1] = scale[2] = 1.0f;
}

void Entity::SetPos(float x, float y, float z)
{
	if (boundBox == NULL) {
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
	}
	else if (!boundBox->GetCollision()) {
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
		boundBox->SetPos(pos[0], pos[1]);
		boundBox->SetCollision(false);
	}
	TranslateMatrix = translate(mat4(1.0f), pos);
	UpdateWorldMatrix();
}
void Entity::SetRot(float x, float y, float z)
{
	rot[0] = x;
	rot[1] = y;
	rot[2] = z;

	RotMatrix = rotate(mat4(1.0f), x, vec3(1.0f, 0.0f, 0.0f));
	RotMatrix *= rotate(mat4(1.0f), y, vec3(0.0f, 1.0f, 0.0f));
	RotMatrix *= rotate(mat4(1.0f), z, vec3(0.0f, 0.0f, 1.0f));

	UpdateWorldMatrix();
}
void Entity::SetScale(float x, float y, float z)
{
	scale[0] = x;
	scale[1] = y;
	scale[2] = z;

	ScaleMatrix = glm::scale(mat4(1.0f), scale);

	UpdateWorldMatrix();
}
void Entity::UpdateWorldMatrix()
{
	WorldMatrix = TranslateMatrix * RotMatrix * ScaleMatrix;
}
vec3 Entity::GetPos()
{
	return pos;
}
vec3 Entity::GetRot()
{
	return rot;
}
glm::vec3 Entity::GetScale()
{
	return scale;
}

void Entity::Translate(float x, float y, float z)
{
	pos[0] += x;
	pos[1] += y;
	pos[2] += z;
	boundBox->SetPos(pos[0], pos[1]);

	TranslateMatrix = translate(mat4(1.0f), pos);
	UpdateWorldMatrix();
}
void Entity::Rotate(float x, float y, float z)
{
	rot[0] += x;
	rot[1] += y;
	rot[2] += z;

	RotMatrix = rotate(mat4(1.0f), rot[0], vec3(1.0f, 0.0f, 0.0f));
	RotMatrix *= rotate(mat4(1.0f), rot[1], vec3(0.0f, 1.0f, 0.0f));
	RotMatrix *= rotate(mat4(1.0f), rot[2], vec3(0.0f, 0.0f, 1.0f));

	UpdateWorldMatrix();
}

void Entity::SetBoundingBox(float width, float heigth) 
{
	boundBox = new BoundingBox(vec2(pos.x, pos.y), width, heigth);
}

BoundingBox* Entity::GetBoundingBox()
{
	return boundBox;
}


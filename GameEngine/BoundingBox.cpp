#include "BoundingBox.h"

//Aca tiene toda la informacion de las cajas de colisiones 

BoundingBox::BoundingBox(glm::vec2 pos, unsigned int w, unsigned int h) :
	boxPosition(pos), width(w), height(h),  collision(false) {
}

float BoundingBox::GetX()
{
	return boxPosition.x;
}

float BoundingBox::GetY()
{
	return boxPosition.y;
}

glm::vec2 BoundingBox::GetPos()
{
	return boxPosition;
}

void BoundingBox::SetPos(float x, float y) {
	boxPosition.x = x;
	boxPosition.y = y;
}

float BoundingBox::GetWidth()
{
	return width;
}

float BoundingBox::GetHeigth()
{
	return height;
}

//---------------------------------------------------
bool BoundingBox::GetCollision()
{
	return collision;
}
//----------------------------------------------------
void BoundingBox::SetCollision(bool value)
{
	collision = value;
}

BoundingBox::~BoundingBox() {
}


#pragma once
#include<list>
#include<vector>
#include"Sprite.h"
#include "Tilemap.h"
#include"BoundingBox.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

using namespace std;

class FRANKENGINE_API CollisionManager
{
private:
	/*Box Collision*/

	void VerticalCollision(Sprite * SpriteA, Sprite * SpriteB,
		BoundingBox * A, BoundingBox * B, float penetrateY);

	void HorizontalCollision(Sprite * SpriteA, Sprite * SpriteB,
		BoundingBox * A, BoundingBox * B, float penetrateX);

	
	CollisionManager();
	static CollisionManager * Instance;
public:
	static CollisionManager * GetInstance();
	
	void CheckColision(Sprite* a, Sprite* b);
	void CheckTileColision(Sprite* a, Tilemap* level, int tileID);
	~CollisionManager();
};

#pragma once
#include "Entity.h"
#include<list>
#include<vector>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

using namespace std;

class FRANKENGINE_API CollisionManager
{
	
private:
	/*Box Collision*/
	

	void VerticalCollision(Entity * EntityA, Entity* EntityB,
		BoundingBox * A, BoundingBox * B, float penetrateY);

	void HorizontalCollision(Entity* EntityA, Entity* EntityB,
		BoundingBox * A, BoundingBox * B, float penetrateX);

	static CollisionManager * Instance;

	void AddEntity(Entity* entidad);

public:
	CollisionManager();

	static CollisionManager * GetInstance();
	
	void MakeCollision(Entity* a, Entity* b);

	void WallCollision(Entity* a);

	bool CheckCollision(Entity* a, Entity* b);

	void CheckTileColision(Entity* a, Entity* level, int tileID);
	~CollisionManager();
};

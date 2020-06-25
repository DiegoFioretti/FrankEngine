#include "CollisionManager.h"

CollisionManager::CollisionManager() {
}
CollisionManager::~CollisionManager() {
}

CollisionManager* CollisionManager::Instance = NULL;

CollisionManager * CollisionManager::GetInstance() {
	if (Instance == NULL) {
		Instance = new CollisionManager();
	}
	return Instance;
}

void CollisionManager::VerticalCollision(Entity* EntityA, Entity* EntityB,
	BoundingBox* A, BoundingBox* B, float penetrateY) {
	

	if (EntityA->GetPos().y >= EntityB->GetPos().y)
	{
		EntityA->SetPos(A->GetX(),A->GetY() + penetrateY , 0);
	}
	else
	{
		EntityA->SetPos(A->GetX(), A->GetY() - penetrateY, 0);
	}


	
}

void CollisionManager::HorizontalCollision(Entity* EntityA, Entity* EntityB,
	BoundingBox* A, BoundingBox* B, float penetrateX) {

	if (EntityA->GetPos().x >= EntityB->GetPos().x)
	{
		EntityA->SetPos(A->GetX() + penetrateX, A->GetY() , 0);
	}
	else
	{
		EntityA->SetPos(A->GetX() - penetrateX, A->GetY() , 0);
	}
}

void CollisionManager::CheckColision(Entity* a, Entity* b) {

	BoundingBox* A = a->GetBoundingBox();
	BoundingBox* B = b->GetBoundingBox();
	vec2 dif = A->GetPos() - B->GetPos();
	float diffX = abs(dif.x);
	float diffY = abs(dif.y);

	if (diffX <= (A->GetWidth() / 2 + B->GetWidth() / 2) &&
		diffY <= (A->GetHeigth() / 2 + B->GetHeigth() / 2)) {

		float penetrateX = (A->GetWidth() / 2 + B->GetWidth() / 2) - diffX;
		float penetrateY = (A->GetHeigth() / 2 + B->GetHeigth() / 2) - diffY;

		if (penetrateX > penetrateY) {
			
			VerticalCollision(a, b, A, B, penetrateY);
		}
		else {
	
			HorizontalCollision(a, b, A, B, penetrateX);
		}
	}
}

void CollisionManager::AddEntity(Entity* entidad) {


}


void CollisionManager::CheckTileColision(Entity* a, Entity* level, int tileID)
{
	/*for (size_t i = 0; i < level->GetTileAmount(); i++)
	{
		if (level->GetTileInfo(tileID)->getTileID() == tileID)
		{
			BoundingBox* A = a->GetBoundingBox();
			BoundingBox* B = level->GetTileInfo(tileID)->GetBoundingBox();
			vec2 dif = A->GetPos() - B->GetPos();
			float diffX = abs(dif.x);
			float diffY = abs(dif.y);

			if (diffX <= (A->GetWidth() / 2 + B->GetWidth() / 2) &&
				diffY <= (A->GetHeigth() / 2 + B->GetHeigth() / 2)) {

				float penetrateX = (A->GetWidth() / 2 + B->GetWidth() / 2) - diffX;
				float penetrateY = (A->GetHeigth() / 2 + B->GetHeigth() / 2) - diffY;

				if (penetrateX > penetrateY) {

					VerticalCollision(a, level->GetTileInfo(tileID), A, B, penetrateY);
				}
				else {

					HorizontalCollision(a, level->GetTileInfo(tileID), A, B, penetrateX);
				}
			}
		}
	}*/
}
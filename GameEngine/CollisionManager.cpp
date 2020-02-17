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

void CollisionManager::VerticalCollision(Sprite * SpriteA, Sprite * SpriteB,
	BoundingBox * A, BoundingBox * B, float penetrateY) {
	

	if (SpriteA->GetPos().y >= SpriteB->GetPos().y)
	{
		SpriteA->SetPos(A->GetX(),A->GetY() + penetrateY , 0);
	}
	else
	{
		SpriteA->SetPos(A->GetX(), A->GetY() - penetrateY, 0);
	}


	
}

void CollisionManager::HorizontalCollision(Sprite * SpriteA, Sprite * SpriteB,
	BoundingBox * A, BoundingBox * B, float penetrateX) {

	if (SpriteA->GetPos().x >= SpriteB->GetPos().x)
	{
		SpriteA->SetPos(A->GetX() + penetrateX, A->GetY() , 0);
	}
	else
	{
		SpriteA->SetPos(A->GetX() - penetrateX, A->GetY() , 0);
	}
}

void CollisionManager::CheckColision(Sprite* a, Sprite* b) {

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

void CollisionManager::CheckTileColision(Sprite* a, Tilemap* level, int tileID)
{
	for (size_t i = 0; i < level->GetTileAmount(); i++)
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
	}
}
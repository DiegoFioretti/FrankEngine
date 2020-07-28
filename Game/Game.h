#include "Gamebase.h"
#include "Triangle.h"
#include "Material.h"
#include "TextureImporter.h"
#include "Sprite.h"
#include "Tilemap.h"
#include "CollisionManager.h"
#include "Input.h"
#include <iostream>

class Game : public GameBase {
private:
	float i;
	Sprite* pollo;
	Sprite* muchacho;
	Sprite* cuadradito;
	
	Tilemap* myLevel;

	Material * material1;

	Input * inp;
	
	CollisionManager* col;

	bool setAnimL = false;
	bool setAnimR = false;
	bool cancel = false;
public:
	Game();
	~Game();
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
};
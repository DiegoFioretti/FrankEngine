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
	int i;
	Sprite* pollo;
	Sprite* muchacho;
	Sprite* cuadradito;

	Tilemap* myLevel;

	Triangle* triangle;

	Material * material1;
	Material * material3;

	Input * inp;
	
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
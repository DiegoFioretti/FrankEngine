#pragma once

#include "Gamebase.h"
#include "Triangle.h"
#include "Material.h"
#include "TextureImporter.h"
#include "Sprite.h"
#include "Tilemap.h"
#include "CollisionManager.h"
#include "Input.h"
#include "Camera.h"
#include "Shader3D.h"
#include "Model.h"
#include "Lighting.h"

#include <iostream>

using namespace std;

class Game2D : public GameBase
{
	Input* inp;

	Sprite* pollo;
	Sprite* muchacho;
	Sprite* cuadradito;

	Tilemap* myLevel;

	Material* material1;


	CollisionManager* col;

	bool setAnimL = false;
	bool setAnimR = false;
	bool cancel = false;

public:
	Game2D();
	~Game2D();
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
};


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

class Game : public GameBase {
private:
	float i;
	//Entity* pollo;
	//Sprite* muchacho;
	//Sprite* cuadradito;

	//Tilemap* myLevel;

	//Triangle* triangle;

	//Material * material1;
	//Material * material3;
	Camera* cam;
	Input * inp;
	
	Shader3D* shader;
	Shader3D* lightingShader;
	Shader3D* boxShader;

	//Lighting* looz;
	//Lighting* lightingShader;

	Model* ourModel;
	Model* boxModel;

	bool light = false;
	bool hold = false;
	glm::vec3 holdPosition;

	float a = -0.2f;
	float b = -1.0f;
	float c = -0.3f;


public:
	Game();
	~Game();
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
};
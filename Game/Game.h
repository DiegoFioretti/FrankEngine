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
	
	Lighting* looz;

	Model* ourModel;

	bool light=true;
	bool hold = false;
	glm::vec3 holdPosition;

public:
	Game();
	~Game();
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
};
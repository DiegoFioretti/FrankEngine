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

	Lighting* looz;
	//Lighting* lightingShader;

	Model* ourModel;
	Model* boxModel;

	bool light = true;
	bool hold = false;
	bool newLight = true;
	glm::vec3 holdPosition;

	glm::vec3 dirDirection = glm::vec3(-0.2f, -1.0f, -0.3f);
	glm::vec3 dirAmbient = glm::vec3 (0.05f, 0.05f, 0.05f);
	glm::vec3 dirDiffuse = glm::vec3(0.4f, 0.4f, 0.4f);
	glm::vec3 dirSpecular = glm::vec3(0.5f, 0.5f, 0.5f);

	glm::vec3 pointAmbient= glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 pointDiffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	glm::vec3 pointSpecular = glm::vec3(1.0f, 1.0f, 1.0f);
	float pointConstant = 1.0f;
	float pointLinear = 0.09f;
	float pointQuadratic = 0.032f;




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
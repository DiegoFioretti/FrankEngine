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

class Game : public GameBase {
private:
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
	Shader3D* boxShader;

	Lighting* looz;

	Model* samusModel;
	Model* clonSamus;
	Model* zeldaModel;

	glm::vec3 offset;

	bool light = true;
	bool hold = false;
	bool newLight = true;
	glm::vec3 holdPosition;

	glm::vec3 dirDirection = glm::vec3(-0.2f, -1.0f, -0.3f);
	glm::vec3 dirAmbient = glm::vec3 (0.005f, 0.005f, 0.005f);
	glm::vec3 dirDiffuse = glm::vec3(0.04f, 0.04f, 0.04f);
	glm::vec3 dirSpecular = glm::vec3(0.5f, 0.5f, 0.5f);

	//Luz Roja
	glm::vec3 pointAmbient = glm::vec3(0.1745f, 0.01175f, 0.01175f);
	glm::vec3 pointDiffuse = glm::vec3(211.f/255.f, 34.f/255.f , 19.f/255.f);
	glm::vec3 pointSpecular = glm::vec3(0.727811f, 0.626959f, 0.626959f);
	//Blanca
	glm::vec3 bpointAmbient= glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 bpointDiffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	glm::vec3 bpointSpecular = glm::vec3(1.0f, 1.0f, 1.0f);
	float pointConstant = 1.0f;
	float pointLinear = 0.09f;
	float pointQuadratic = 0.032f;



	//LUZ: 7.4 , 14.7 , 5.8 ,
	float a = -0.2f;
	
	float b = 7.4f;
	float c = 14.7f;
	float d = 5.8f;

public:
	Game();
	~Game();
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	void OnDraw() override;
};


/*Dudas:
camera.cpp

*/
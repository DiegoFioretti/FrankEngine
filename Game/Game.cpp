#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::OnStart() 
{	
	i = 0;
	render->setClearScreenColor(0.2f,0.2f,0.2f,1.0f);

	//shader = lightingShader();
	lightingShader = new Shader3D("Lighting/BasicLightingVS.txt", "Lighting/BasicLightingFS.txt");
	shader = new Shader3D("ModelVS3D.txt", "ModelFS3D.txt");
	ourModel = new Model("Metroid/DolSzerosuitR1.obj");

	//lightShader = new Shader3D("BasicLightingVS","BasicLightingFS");

	inp = new Input(window);

	return true;
}
//RECORDATORIO crear delta time
bool Game::OnUpdate() {

	

	glm::vec3 lightColor(0.9f, 0.0f, 0.9f);

	shader->use();
	// view/projection transformations
	shader->setMat4("projection", cam->GetProjectionMatrix());
	shader->setMat4("view", cam->GetViewMatrix());
	shader->setVec3("LightColor", lightColor);

	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.0f));
	shader->setMat4("model", model);
	//-------------------------------------LUZ-----------------------------------------
	if (cosa)
	{
	// be sure to activate shader when setting uniforms/drawing objects
	lightingShader->use();
	lightingShader->setVec3("lightPos", 1.2f, 1.0f, 2.0f);
	lightingShader->setVec3("viewPos", cam->GetCameraPos());

	// light properties
	
	glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.9f); // low influence
	lightingShader->setVec3("light.ambient", ambientColor);
	lightingShader->setVec3("light.diffuse", diffuseColor);
	lightingShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

	// material properties
	lightingShader->setVec3("material.ambient", 0.5f, 0.5f, 0.3f);
	lightingShader->setVec3("material.diffuse", 0.5f, 0.5f, 0.3f);
	lightingShader->setVec3("material.specular", 0.5f, 0.5f, 0.5f); 
	lightingShader->setFloat("material.shininess", 50.0f);

	// view/projection transformations
	lightingShader->setMat4("projection", cam->GetProjectionMatrix());
	lightingShader->setMat4("view", cam->GetViewMatrix());

	// world transformation
	glm::mat4 modelLight = glm::mat4(1.0f);
	lightingShader->setMat4("model", modelLight*model);
	}

	
	


	//Inputs (letra a tocar, 0 const y 1 una sola vez)
	if (inp->keyCall("Space", 0)) {
		cam->CameraMoveForward(0.5f);
	}

	//Mov camara
	if (inp->keyCall('a', 0)) {
		cam->CameraMoveLeft(0.3f);
	}
	if (inp->keyCall('d', 0)) {
		cam->CameraMoveLeft(-0.3f);
	}
	if (inp->keyCall('w', 0)) {
		cam->CameraMoveForward(0.5f);
	}
	if (inp->keyCall('s', 0)) {
		cam->CameraMoveForward(-0.5f);
	}
	if (inp->keyCall('q', 0)) {
		cam->CameraTranslateY(-0.5f);
	}
	if (inp->keyCall('e', 0)) {
		cam->CameraTranslateY(0.5f);
	}

	if (inp->keyCall('r', 1)) {
		if (cosa==true)
			cosa = false;
		else
			cosa = true;
		
	}
	return true;

/*pollo->SetAnim(3, 5, 0.1f);
		pollo->Translate(0.1f, 0.0f, 0.0f);*/
}

//Esto es lo que determina que va a dibujarse
void Game::OnDraw(){

	ourModel->Draw(*shader);
}

bool Game::OnStop() {

	delete inp;

	delete shader;
	delete lightingShader;
	delete ourModel;

	delete pollo;
	return false;
}



//material3 = new Material();	
//material3->LoadShaders("colorvertexshader.txt", "colorfragmentshader.txt");	

//pollo = new Sprite(render, 3, 4);//le pasas el renderer a utilizar y le decis por cuanto cortas el spritesheet
//pollo->SetMaterial(material1); // le asignas el material 
//pollo->LoadMaterial("spritesheet_chicken.bmp"); // le pasas el archivo a cortar (BMP es un archivo nativo del window)
//pollo->SetPos(0, 0, 0);// Asigna la posicion
//pollo->SetBoundingBox(2.0f, 2.0f);// le seteas el ancho y alto de la caja de colisiones
//pollo->SetAnim(0, 11, 1.1f);// desde que frame arranca y hasta cual termina, mas el tiempo de duracion total

//muchacho = new Sprite(render, 4, 4);
//muchacho->SetMaterial(material1);
//muchacho->LoadMaterial("spritesheet_caveman.bmp");
//muchacho->SetPos(3, 3, 0);
//muchacho->SetBoundingBox(2.0f, 2.0f);
//muchacho->SetAnim(0, 15, 0.1f);	

//cuadradito = new Sprite(render, 1, 1);
//cuadradito->SetMaterial(material1);
//cuadradito->LoadMaterial("angry.bmp");
//cuadradito->SetPos(1, -8, 0);
//cuadradito->SetBoundingBox(2.0f, 2.0f);

	//triangle = new Triangle(render);
	//triangle->SetMaterial(material3);
	//triangle->SetPos(-3, 5, 0);

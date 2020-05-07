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

	looz = new Lighting("Lighting/BasicLightingVS.txt", "Lighting/BasicLightingFS.txt");
	shader = new Shader3D("ModelVS3D.txt", "ModelFS3D.txt");

	ourModel = new Model("Gun/Gun.fbx");

	inp = new Input(window);

	return true;
}
//RECORDATORIO crear delta time
bool Game::OnUpdate() {
	i++;
	shader->use();
	// view/projection transformations
	shader->setMat4("projection", cam->GetProjectionMatrix());
	shader->setMat4("view", cam->GetViewMatrix());

	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
	shader->setMat4("model", model);

	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
	shader->setVec3("LightColor", lightColor);



	//-------------------------------------LUZ-----------------------------------------
	if (light)
	{
	// be sure to activate shader when setting uniforms/drawing objects
		looz->use();
		looz->position(cam->GetCameraPos());
		looz->viewPosition(cam->GetCameraPos());
		looz->lightPropierties("base");
		looz->materialPropierties("emerald");
		looz->viewProyection(cam->GetViewMatrix(), cam->GetProjectionMatrix());
		looz->modelLight(model);
	}

	//Inputs (letra a tocar, 0 const y 1 una sola vez)
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

	if (inp->keyCall('t', 1)) {
		if (hold == true) {
			hold = false;
		}
		else {
			hold = true;
			holdPosition = cam->GetCameraPos();
		}
	}
	if (inp->keyCall('r', 1)) {
		if (light == true)
			light = false;
		else
			light = true;
	}
	return true;

/*pollo->SetAnim(3, 5, 0.1f);
		pollo->Translate(0.1f, 0.0f, 0.0f);*/
}

//Esto es lo que determina que va a dibujarse
void Game::OnDraw(){

		ourModel->Draw(*looz);
}

bool Game::OnStop() {

	delete inp;

	delete shader;
	delete looz;
	delete ourModel;

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

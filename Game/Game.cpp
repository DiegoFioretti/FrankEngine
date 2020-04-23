#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::OnStart() 
{	

	//creamos los materiales y les cargamos los shaders
	material1 = new Material();
	material1->LoadShaders("VertexTexture.txt", "FragmentTexture.txt");

	myLevel = new Tilemap( -10 , 10, 0);
	myLevel->loadBMPTileset(render, material1, "Empty.bmp", 2, 2);
	myLevel->loatTXTTilemap("Tilemap.txt", 10, 10);


	shader = new Shader3D("ModelVS3D.txt", "ModelFS3D.txt");
	ourModel = new Model("Metroid/DolSzerosuitR1.obj");

	ourShader = new Shader3D("Lighting/BasicLightingVS","Lighting/BasicLightingFS");

	
	inp = new Input(window);

	return true;
}
//RECORDATORIO crear delta time
bool Game::OnUpdate() {
	//shader->use();

	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); 
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	
	//shader->setMat4("model", model);


	glm::vec3 lightPos(1.2f, 10.0f, 2.0f);
	// be sure to activate shader when setting uniforms/drawing objects
	ourShader->use();
	ourShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
	ourShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	ourShader->setVec3("lightPos", lightPos);
	ourShader->setVec3("viewPos", cam->GetCameraPos());

	// view/projection transformations
	ourShader->setMat4("projection", cam->GetProjectionMatrix());
	ourShader->setMat4("view", cam->GetViewMatrix());

	// world transformation
	//model = glm::mat4(1.0f);
	ourShader->setMat4("model", model);



	
	
	//Inputs (letra a tocar, 0 const y 1 una sola vez)
	if (inp->keyCall("Space", 0)) {
		
		//render->MainCamera()->CameraMoveForward(0.5f);
		//window->CameraTranslate(0.0f,0.0f,0.5f);
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


	if (inp->keyCall('r', 0)) {
		render->setClearScreenColor(0.8f,0.42,0.23f,1.0f);
	}
	return true;

		/*pollo->SetAnim(3, 5, 0.1f);
		pollo->Translate(0.1f, 0.0f, 0.0f);*/

}

//Esto es lo que determina que va a dibujarse
void Game::OnDraw(){
	
	
	myLevel->DrawTiles();
	ourModel->Draw(*shader);
	
}

bool Game::OnStop() {

	delete material1;
	
	delete myLevel;
	delete inp;

	delete shader;
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


//chequea las colisiones entre 2 sprites
	//CollisionManager::GetInstance()->CheckColision(pollo,muchacho);
	//CollisionManager::GetInstance()->CheckTileColision(pollo, myLevel, 2);
	//CollisionManager::GetInstance()->CheckColision(pollo,caja);

	//esto es cada cuanto suma la animacion, en un futuro sera un DeltaTime
	//muchacho->UpdAnim(0.05f);
	//pollo->UpdAnim(0.05f);
	//triangle->SetRot(0.0f, 0.0f, i / 5);

//myLevel->UpdateTilesAnim(0.05f);
	//pollo->Draw();
	//muchacho->Draw();	

	//triangle->Draw();
	//cuadradito->Draw();

//delete material3;



	//delete triangle;

	//delete pollo;
	//delete muchacho;
	//delete cuadradito;
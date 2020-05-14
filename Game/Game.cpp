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

	//looz = new Lighting("Lighting/BasicLightingVS.txt", "Lighting/BasicLightingFS.txt");
	lightingShader = new Shader3D("Lighting/MultiLightVS.txt", "Lighting/MultiLightFS.txt");

	shader = new Shader3D("ModelVS3D.txt", "ModelFS3D.txt");
	boxShader= new Shader3D("ModelVS3D.txt", "ModelFS3D.txt");

	ourModel = new Model("Metroid/DolSzerosuitR1.obj");
	ourModel->SetPos(glm::vec3(0.0f, 0.0f, 0.0f));
	ourModel->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	boxModel = new Model("Link/source/zeldaPosed001.fbx");
	boxModel->SetPos(glm::vec3(0.0f, 0.0f, 0.0f));
	boxModel->SetScale(glm::vec3(0.1f, 0.1f, 0.1f));

	inp = new Input(window);

	return true;
}
//RECORDATORIO crear delta time
bool Game::OnUpdate() {
	i++;
	

	
	
	//-------------------------------------LUZ-----------------------------------------
	if (light)
	{
	// be sure to activate shader when setting uniforms/drawing objects
	/*	looz->use();
		looz->position(cam->GetCameraPos());
		looz->viewPosition(cam->GetCameraPos());
		looz->lightPropierties("base");
		looz->materialPropierties("base");
		looz->viewProyection(cam->GetViewMatrix(), cam->GetProjectionMatrix());
		looz->modelLight(ourModel->GetWorldMatrix());*/
	}
	//-----
	glm::vec3 pointLightPositions[] = {
		glm::vec3(1.0f,  0.0f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	lightingShader->use();
	lightingShader->setVec3("viewPos", cam->GetCameraPos());
	lightingShader->setFloat("material.shininess", 32.0f);
	/*
	   Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
	   the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
	   by defining light types as classes and set their values in there, or by using a more efficient uniform approach
	   by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
	*/
	// directional light
	lightingShader->setVec3("dirLight.direction", a, b, c);
	lightingShader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	lightingShader->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	lightingShader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
	
	// point light 1
	lightingShader->setVec3("pointLights[0].position", pointLightPositions[0]);
	lightingShader->setVec3("pointLights[0].ambient", 0.5f, 0.5f, 0.5f);
	lightingShader->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
	lightingShader->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
	lightingShader->setFloat("pointLights[0].constant", 1.0f);
	lightingShader->setFloat("pointLights[0].linear", 0.09);
	lightingShader->setFloat("pointLights[0].quadratic", 0.032);
	/*// point light 2
	lightingShader->setVec3("pointLights[1].position", pointLightPositions[1]);
	lightingShader->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
	lightingShader->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
	lightingShader->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
	lightingShader->setFloat("pointLights[1].constant", 1.0f);
	lightingShader->setFloat("pointLights[1].linear", 0.09);
	lightingShader->setFloat("pointLights[1].quadratic", 0.032);
	// point light 3
	lightingShader->setVec3("pointLights[2].position", pointLightPositions[2]);
	lightingShader->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
	lightingShader->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
	lightingShader->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
	lightingShader->setFloat("pointLights[2].constant", 1.0f);
	lightingShader->setFloat("pointLights[2].linear", 0.09);
	lightingShader->setFloat("pointLights[2].quadratic", 0.032);
	// point light 4
	lightingShader->setVec3("pointLights[3].position", pointLightPositions[3]);
	lightingShader->setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
	lightingShader->setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
	lightingShader->setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
	lightingShader->setFloat("pointLights[3].constant", 1.0f);
	lightingShader->setFloat("pointLights[3].linear", 0.09);
	lightingShader->setFloat("pointLights[3].quadratic", 0.032);*/
	// spotLight
	lightingShader->setVec3("spotLight.position", cam->GetCameraPos());
	lightingShader->setVec3("spotLight.direction", cam->GetCameraDir());
	lightingShader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	lightingShader->setVec3("spotLight.diffuse", 0.0f, 0.0f, 0.0f);
	lightingShader->setVec3("spotLight.specular", 0.0f, 0.0f, 0.0f);
	lightingShader->setFloat("spotLight.constant", 1.0f);
	lightingShader->setFloat("spotLight.linear", 0.09);
	lightingShader->setFloat("spotLight.quadratic", 0.032);
	lightingShader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	lightingShader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
	
	// view/projection transformations

	lightingShader->setMat4("projection", cam->GetProjectionMatrix());
	lightingShader->setMat4("view", cam->GetViewMatrix());

	// world transformation
	glm::mat4 model = glm::mat4(1.0f);
	lightingShader->setMat4("model", ourModel->GetWorldMatrix());
	ourModel->SetPos(glm::vec3(a, 0.0f, 0.0f));
	//-----

	//Inputs (letra a tocar, 0 const y 1 una sola vez)
	//Mov camara
	if (inp->keyCall('t', 0)) {
		cout << boxModel->GetPos().x << endl;
	}
	if (inp->keyCall('a', 0)) {
		cam->CameraMoveLeft(0.3f);
	}
	if (inp->keyCall('d', 0)) {
		cam->CameraMoveLeft(-0.3f);
	}
	if (inp->keyCall('w', 0)) {
		cam->CameraMoveForward(0.1f);
	}
	if (inp->keyCall('s', 0)) {
		cam->CameraMoveForward(-0.1f);
	}
	if (inp->keyCall('q', 0)) {
		cam->CameraTranslateY(-0.1f);
	}
	if (inp->keyCall('e', 0)) {
		cam->CameraTranslateY(0.1f);
	}
	if (inp->keyCall('o', 0)) {
		a += 0.1;
	}
	if (inp->keyCall('i', 0)) {
		a -= 0.1;
	}
	if (inp->keyCall('j', 0)) {
		b += 0.1;
	}
	if (inp->keyCall('k', 0)) {
		b -= 0.1;
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
	shader->use();
	// view/projection transformations
	shader->setMat4("projection", cam->GetProjectionMatrix());
	shader->setMat4("view", cam->GetViewMatrix());
	// render the loaded model
	shader->setMat4("model", ourModel->GetWorldMatrix());
	ourModel->Draw(*shader);

	boxShader->use();
	// view/projection transformations
	boxShader->setMat4("projection", cam->GetProjectionMatrix());
	boxShader->setMat4("view", cam->GetViewMatrix());
	// render the loaded model
	boxShader->setMat4("model", boxModel->GetWorldMatrix());
	boxModel->Draw(*boxShader);
}

bool Game::OnStop() {

	delete inp;

	delete shader;
	delete boxShader;
	//delete looz;
	delete ourModel;
	delete boxModel;
	delete lightingShader;

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

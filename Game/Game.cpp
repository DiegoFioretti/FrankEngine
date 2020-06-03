#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::OnStart() 
{	
	render->setClearScreenColor(0.2f,0.2f,0.2f,1.0f);

	looz = new Lighting("Lighting/MultiLightVS.txt", "Lighting/MultiLightFS.txt",2);
	
	shader = new Shader3D("ModelVS3D.txt", "ModelFS3D.txt");

	samusModel = new Model("Metroid/DolSzerosuitR1.obj");
	samusModel->SetPos(glm::vec3(0.0f, 0.0f, 0.0f));
	samusModel->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	zeldaModel = new Model("Link/source/zeldaPosed001.fbx");
	zeldaModel->SetPos(glm::vec3(10.0f, 0.0f, 0.0f));
	zeldaModel->SetScale(glm::vec3(0.1f, 0.1f, 0.1f));

	clonSamus = new Model("Metroid/DolSzerosuitR1.obj");
	clonSamus->SetPos(glm::vec3(0.0f, 0.0f, 0.0f));
	clonSamus->SetPos(glm::vec3(20.0f, 0.0f, 0.0f));

	inp = new Input(window);

	cam->setCameraPos(10.0f, 7.0f, 31.0f);
	cam->setCameraRot(-90.0f, 5.5f);

	return true;
}

//RECORDATORIO crear delta time
bool Game::OnUpdate() {
	//-------------------------------------LUZ-----------------------------------------
	offset = glm::vec3(zeldaModel->GetPos().x- 1.56252f, zeldaModel->GetPos().y+14.43748f, zeldaModel->GetPos().z + 5.24109f);

	glm::vec3 pointLightPositions[] = {
		glm::vec3(-2.68787f+a,  14.8674f,  2.34049f),
		glm::vec3(offset.x , offset.y, offset.z),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	
	looz->use();
	looz->viewPosition(cam->GetCameraPos());
	looz->materialShiness(70.0f);
	looz->directionalPropierties(dirDirection, dirAmbient, dirDiffuse, dirSpecular);
	looz->pointLight(0,pointLightPositions[0], bpointAmbient, bpointDiffuse, bpointSpecular, pointConstant, pointLinear, pointQuadratic);
	looz->pointLight(1,pointLightPositions[1], pointAmbient, pointDiffuse, pointSpecular, pointConstant, pointLinear, pointQuadratic);
	//looz->spotLight("null");
	looz->spotLight("base", cam->GetCameraPos(), cam->GetCameraDir());
	looz->viewProyection(cam->GetViewMatrix(), cam->GetProjectionMatrix());


	samusModel->SetPos(glm::vec3(a, 0.0f, 0.0f));
	

	//Inputs (letra a tocar, 0 const y 1 una sola vez)
	if (inp->keyCall('t', 0)) {
		cout << zeldaModel->GetPos().x << endl;
		cout << offset.x<<endl;
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
		//cout << "Zelda x=" << zeldaModel->GetPos().x << endl;
		//cout << "Zelda y=" << zeldaModel->GetPos().y << endl;
		//cout << "Zelda z=" << zeldaModel->GetPos().z << endl;
		//cout << "Camara x=" << cam->GetCameraDir().x << endl;
		//cout << "Camara y=" << cam->GetCameraDir().y << endl;
		//cout << "Camara z=" << cam->GetCameraDir().z << endl;
		cout << "Camara yaw=" << cam->GetCameraYaw() << endl;
		cout << "Camara pitch=" << cam->GetCameraPitch() << endl;
		

	}
	if (inp->keyCall('k', 0)) {
		zeldaModel->Translate(0.5f,0.f,0.f);
		offset.x = +0.5f;
	}
	
	
	return true;
}

//Esto es lo que determina que va a dibujarse
void Game::OnDraw(){

	
	looz->modelLight(zeldaModel->GetWorldMatrix());
	zeldaModel->Draw(*looz);

	looz->modelLight(samusModel->GetWorldMatrix());
	samusModel->Draw(*looz);

	looz->modelLight(clonSamus->GetWorldMatrix());
	clonSamus->Draw(*looz);
	
}

bool Game::OnStop() {

	delete inp;

	delete shader;
	delete looz;
	delete samusModel;
	delete zeldaModel;
	delete clonSamus;

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





//-----



//----- LINGHTIG
//
//if (true)
//{
//	lightingShader->use();
//	lightingShader->setVec3("viewPos", cam->GetCameraPos());
//	lightingShader->setFloat("material.shininess", 32.0f);
//	/*
//	   Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
//	   the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
//	   by defining light types as classes and set their values in there, or by using a more efficient uniform approach
//	   by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
//	*/
//
//	// directional light
//	lightingShader->setVec3("dirLight.direction", a, b, c);
//	lightingShader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
//	lightingShader->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
//	lightingShader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
//
//	// point light 1
//	lightingShader->setVec3("pointLights[0].position", pointLightPositions[0]);
//	lightingShader->setVec3("pointLights[0].ambient", 0.5f, 0.5f, 0.5f);
//	lightingShader->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
//	lightingShader->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
//	lightingShader->setFloat("pointLights[0].constant", 1.0f);
//	lightingShader->setFloat("pointLights[0].linear", 0.09f);
//	lightingShader->setFloat("pointLights[0].quadratic", 0.032f);
//	// point light 2
//	lightingShader->setVec3("pointLights[1].position", pointLightPositions[1]);
//	lightingShader->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
//	lightingShader->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
//	lightingShader->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
//	lightingShader->setFloat("pointLights[1].constant", 1.0f);
//	lightingShader->setFloat("pointLights[1].linear", 0.09);
//	lightingShader->setFloat("pointLights[1].quadratic", 0.032);
//	// point light 3
//	lightingShader->setVec3("pointLights[2].position", pointLightPositions[2]);
//	lightingShader->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
//	lightingShader->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
//	lightingShader->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
//	lightingShader->setFloat("pointLights[2].constant", 1.0f);
//	lightingShader->setFloat("pointLights[2].linear", 0.09);
//	lightingShader->setFloat("pointLights[2].quadratic", 0.032);
//	// point light 4
//	lightingShader->setVec3("pointLights[3].position", pointLightPositions[3]);
//	lightingShader->setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
//	lightingShader->setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
//	lightingShader->setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
//	lightingShader->setFloat("pointLights[3].constant", 1.0f);
//	lightingShader->setFloat("pointLights[3].linear", 0.09);
//	lightingShader->setFloat("pointLights[3].quadratic", 0.032);
//	// spotLight
//	lightingShader->setVec3("spotLight.position", cam->GetCameraPos());
//	lightingShader->setVec3("spotLight.direction", cam->GetCameraDir());
//	lightingShader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
//	lightingShader->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
//	lightingShader->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
//	lightingShader->setFloat("spotLight.constant", 1.0f);
//	lightingShader->setFloat("spotLight.linear", 0.09);
//	lightingShader->setFloat("spotLight.quadratic", 0.032);
//	lightingShader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
//	lightingShader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
//
//	// view/projection transformations
//
//	lightingShader->setMat4("projection", cam->GetProjectionMatrix());
//	lightingShader->setMat4("view", cam->GetViewMatrix());
//
//	// world transformation
//	glm::mat4 model = glm::mat4(1.0f);
//	lightingShader->setMat4("model", ourModel->GetWorldMatrix());
//}
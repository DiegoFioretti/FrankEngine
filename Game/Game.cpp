#include "Game.h"

// ver con assimp herencias
// tiene que ser un arbol si la cabeza se mueve los ojos tambien
Game::Game()
{
}

Game::~Game()
{
}

bool Game::OnStart() 
{	

	render->setClearScreenColor(0.2f,0.2f,0.7f,1.0f);

	looz = new Lighting("Lighting/MultiLightVS.txt", "Lighting/MultiLightFS.txt",2);
	
	cout << endl;
	//cout << "samus" << endl;
	samusModel = new Model("Metroid/DolSzerosuitR1.obj");
	samusModel->SetPos(glm::vec3(0.0f, 0.0f, 0.0f));
	samusModel->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	cout << "zelda" << endl;
	//mesh_terrain
	zeldaModel = new Model("Link/source/zeldaPosed001.fbx");
	zeldaModel->SetPos(glm::vec3(10.0f, 0.0f, 0.0f));
	zeldaModel->SetScale(glm::vec3(0.1f, 0.1f, 0.1f));


//	clonSamus = new Model("box5.fbx");
//	clonSamus->SetPos(glm::vec3(0.0f, 0.0f, 0.0f));
//	clonSamus->SetPos(glm::vec3(20.0f, 0.0f, 0.0f));



	cam->setCameraPos(10.0f, 7.0f, 31.0f);
	cam->setCameraRot(-90.0f, 5.5f);
	inp = new Input(window);

	return true;
}

//RECORDATORIO crear delta time
bool Game::OnUpdate() {
	//-------------------------------------LUZ-----------------------------------------
	offset = glm::vec3(zeldaModel->GetPos().x+b, zeldaModel->GetPos().y+c, zeldaModel->GetPos().z+d );

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
	
	//samusModel->SetPos(glm::vec3(a, 0.0f, 0.0f));


	//Inputs (letra a tocar, 0 const y 1 una sola vez)
	//Movimiento
	if (inp->keyCall('a', 0)) {
		cam->CameraMoveLeft(10.f * DeltaTime());
	}
	if (inp->keyCall('d', 0)) {
		cam->CameraMoveLeft(-10.f * DeltaTime());
	}
	if (inp->keyCall('w', 0)) {
		cam->CameraMoveForward(10.f * DeltaTime());
	}
	if (inp->keyCall('s', 0)) {
		cam->CameraMoveForward(-10.f * DeltaTime());
	}


	if (inp->keyCall('r', 1)) {
		zeldaModel->GetNames();
	}


	//Samus y luz
	if (inp->keyCall('o', 0)) {
		cout << "Zelda: " << zeldaModel->GetPos().x << " , " << zeldaModel->GetPos().y << " , " << zeldaModel->GetPos().z << " , " << endl;
	}

	//zelda hijo
	if (inp->keyCall('b', 0)) {
		zeldaModel->MoveChildren("mesh_torch",0.01f,0.f,0.f);
		//cout << "aaa" << endl;
	}
 
	// todo Zelda
	if (inp->keyCall('j', 0)) {
		zeldaModel->Translate(0.1f,0,0);
	}
	if (inp->keyCall('v', 0)) {
		zeldaModel->Rotate(0.1f, 0, 0);
	}

	return true;
}

//Esto es lo que determina que va a dibujarse
void Game::OnDraw(){

	//looz->modelLight(zeldaModel->GetWorldMatrix());
	zeldaModel->Draw(*looz);
	//zeldaModel->DrawBox(*shader);

	//looz->modelLight(samusModel->GetWorldMatrix());
	//samusModel->Draw(*looz);

	//looz->modelLight(clonSamus->GetWorldMatrix());
	//clonSamus->Draw(*looz);
	
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
/*
bool Game::OnStart(){
	//creamos los materiales y les cargamos los shaders
	material1 = new Material();
	material1->LoadShaders("VertexTexture.txt", "FragmentTexture.txt");

	
	pollo = new Sprite( 3, 4);//le pasas el renderer a utilizar y le decis por cuanto cortas el spritesheet
	pollo->SetMaterial(material1); // le asignas el material 
	pollo->LoadTexture("spritesheet_chicken.bmp"); // le pasas el archivo a cortar (BMP es un archivo nativo del window)
	pollo->SetPos(0, 0, 0);// Asigna la posicion
	pollo->SetBoundingBox(2.0f, 2.0f);// le seteas el ancho y alto de la caja de colisiones
	pollo->SetAnim(0, 11, 1.1f);// desde que frame arranca y hasta cual termina, mas el tiempo de duracion total

	muchacho = new Sprite( 4, 4);
	muchacho->SetMaterial(material1);
	muchacho->LoadTexture("spritesheet_caveman.bmp");
	muchacho->SetPos(3, 3, 0);
	muchacho->SetBoundingBox(2.0f, 2.0f);
	muchacho->SetAnim(0, 15, 0.1f);	
	
	cuadradito = new Sprite( 1, 1);
	cuadradito->SetMaterial(material1);
	cuadradito->LoadTexture("angry.bmp");
	cuadradito->SetPos(1, -8, 0);
	cuadradito->SetBoundingBox(2.0f, 2.0f);


	myLevel = new Tilemap( -10 , 10, 0);// Creamos el tilemap y le decimos donde se va a ubicar en el mundo
	myLevel->loadBMPTileset(material1, "FinalTile.bmp", 2, 2);// se le indica el material que va a usar, la imagen y de cuanto se compone dicha imagen 
	myLevel->loatTXTTilemap("Tilemap.txt", 10, 10);// le pasas el TXT con la informacion del tilemap y el tamano del mismo

	inp = new Input(window);
	return true;
}


bool Game::OnUpdate() {
	

	//Actualizamos la animacion x el delta time
	muchacho->UpdAnim(DeltaTime());
	pollo->UpdAnim(DeltaTime());

	//Creamos colisiones con los sprites 
	//El 2do sprite es inamobible (esto significa que si invertimos el orden de pollo y muchacho el pollo puede mover a muchacho) 
	col->MakeCollision(pollo, muchacho);
	col->MakeCollision(pollo, cuadradito);
	
	//Aqui se crean las colisiones de los tiles 
	myLevel->MakeColTile(pollo, 0);
	myLevel->MakeColTile(pollo, 2);

	//Esto es un trigger enter sirve para detectar la colision sin generarla
	if (col->CheckCollision(pollo, muchacho)){
		cout << " " << endl;
	}

	if (inp->keyCall('a', 0)) {
		pollo->SetAnim(0, 2, 0.1f);
		pollo->Translate(-10.53f*DeltaTime() , 0.0f, 0.0f);
	}
	if (inp->keyCall('d', 0)) {
		pollo->SetAnim(3, 5, 0.1f);
		pollo->Translate(10.53f * DeltaTime(), 0.0f, 0.0f);
	}
	if (inp->keyCall('w', 0)) {
		pollo->Translate(0, 10.03f * DeltaTime(), 0);
	}
	if (inp->keyCall('s', 0)) {
		pollo->Translate(0, -10.03f * DeltaTime(), 0);
	}
}


//Esto es lo que determina que va a dibujarse
void Game::OnDraw(){
		myLevel->DrawTiles();
		cuadradito->Draw();
		pollo->Draw();
		muchacho->Draw();

}

bool Game::OnStop() {
	delete material1;
	delete pollo;
	delete muchacho;
	delete cuadradito;

	return false;
}

	
*/
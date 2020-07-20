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
	//creamos los materiales y les cargamos los shaders
	material1 = new Material();
	material1->LoadShaders("VertexTexture.txt", "FragmentTexture.txt");

	material3 = new Material();	
	material3->LoadShaders("colorvertexshader.txt", "colorfragmentshader.txt");	

	
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

	myLevel = new Tilemap( -10 , 10, 0);
	myLevel->loadBMPTileset(material1, "Verde.bmp", 2, 2);
	myLevel->loatTXTTilemap("Tilemap.txt", 10, 10);

	triangle = new Triangle();
	triangle->SetMaterial(material3);
	triangle->SetPos(-3, 5, 0);

	inp = new Input(window);

	return true;
}
//RECORDATORIO crear delta time
bool Game::OnUpdate() {

	//chequea las colisiones entre 2 sprites
	//CollisionManager::GetInstance()->MakeCollision(pollo,muchacho);
	//CollisionManager::GetInstance()->CheckTileColision(pollo, myLevel, 2);
	//CollisionManager::GetInstance()->CheckColision(pollo,caja);
	
	muchacho->UpdAnim(DeltaTime());
	pollo->UpdAnim(DeltaTime());
	triangle->SetRot(0.0f, 0.0f, i / 5);


	col->MakeCollision(pollo,muchacho);
	col->MakeCollision(pollo, cuadradito);

	if (col->CheckCollision(pollo, muchacho)){
		//cout << "aaaaaaaaaaaaaaaa" << endl;
	}

	//Inputs (letra a tocar, 0 const y 1 una sola vez)

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
	if (inp->keyCall('g', 0)) {
		pollo->SetScale(pollo->GetScale().x+0.01f,1.0f,0);
	}
	if (inp->keyCall('r', 0)) {
		render->setClearScreenColor(0.8f,0.42,0.23f,1.0f);
	}

	return true;
}

//Esto es lo que determina que va a dibujarse
void Game::OnDraw(){

		myLevel->DrawTiles();
		cuadradito->Draw();
		pollo->Draw();
		muchacho->Draw();
	
	
	
	//triangle->Draw();
}


bool Game::OnStop() {

	delete material1;
	delete material3;

	//delete myLevel;

	delete triangle;

	delete pollo;
	delete muchacho;
	delete cuadradito;

	delete inp;

	return false;
}

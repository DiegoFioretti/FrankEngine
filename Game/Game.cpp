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
	//samusModel = new Model("Nano/nanosuit.obj");
	//samusModel->SetPos(glm::vec3(0.0f, 0.0f, 0.0f));
	//samusModel->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	cout << "zelda" << endl;
	//mesh_terrain
	zeldaModel = new Model("Link/source/zeldaPosed001.fbx");
	zeldaModel->SetPosM(glm::vec3(1.0f, 5.0f, 8.0f));
	zeldaModel->SetScaleChilden(glm::vec3(0.3f, 0.3f, 0.3f));

	zeldaModelt = new Model("Link/source/zeldaPosed001.fbx");
	zeldaModelt->SetPosM(glm::vec3(6.0f, 5.0f, 8.0f));
	zeldaModelt->SetScaleChilden(glm::vec3(0.3f, 0.3f, 0.3f));

//	clonSamus = new Model("box5.fbx");
//	clonSamus->SetPos(glm::vec3(0.0f, 0.0f, 0.0f));
//	clonSamus->SetPos(glm::vec3(20.0f, 0.0f, 0.0f));

	cam = render->MainCamera();

	cam->setCameraPos(10.0f, 7.0f, 31.0f);
	cam->setCameraRot(-90.0f, 0.0f);
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
	if (inp->keyCall('o', 1)) {
		//cout << "Zelda: " << zeldaModel->GetPos().x << " , " << zeldaModel->GetPos().y << " , " << zeldaModel->GetPos().z << " , " << endl;
		zeldaModel->Db_CheckIfInFrustrum();
		cout << zeldaModel->GetPos().x << endl;
		cout << zeldaModel->GetPos().y << endl;
		cout << zeldaModel->GetPos().z << endl;
		for (size_t i = 0; i < 6; i++)
		{
			zeldaModel->GetChildPos(i);
		}
		
	}

	//zelda hijo
	if (inp->keyCall('b', 0)) {
		zeldaModel->MoveChildren("mesh_torch", 1.01f * DeltaTime(),0.f,0.f);
		//cout << "aaa" << endl;
	}
 
	// todo Zelda
	if (inp->keyCall('j', 0)) {
		zeldaModel->MTranslate(0,10.f * DeltaTime(),0);
	}
	if (inp->keyCall('n', 0)) {
		zeldaModel->MTranslate(0, -10.f * DeltaTime(), 0);
	}

	return true;
}

//Esto es lo que determina que va a dibujarse
void Game::OnDraw(){

	//looz->modelLight(zeldaModel->GetWorldMatrix());
	zeldaModel->Draw(*looz);
	zeldaModelt->Draw(*looz);
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

	
*/
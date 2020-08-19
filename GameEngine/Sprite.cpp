#include "Sprite.h"

// Para dibujar con textura 
Sprite::Sprite( int columns, int rows)  {
	onCollision = false;
	anim = new Animation(columns, rows);
	uvArray = anim->UpdateAnimation(0);

	SetTextureVertex(uvArray, 4);
}

void Sprite::SetTextureVertex(float * vertices, int count) {
	DisposeTexture();

	ShouldDispouseTexture = true;
	uvBufferID = render->GenBuffer(vertices, sizeof(float) * count * 2);
	
}


void Sprite::DisposeTexture() {
	if (ShouldDispouseTexture)
	{
		render->DestroyBuffer(uvBufferID);
		ShouldDispouseTexture = false;
	}
}

void Sprite::SetAnim(int initF, int finishF, float timePerF) {
	if (initF != animB ){
		animB = initF;
		anim->SetAnimation(initF, finishF, timePerF);
	}
	if (finishF != animE){
		animE = finishF;
		anim->SetAnimation(initF, finishF, timePerF);
	}
	
}


void Sprite::UpdAnim(float deltaTime) {
	uvArray = anim->UpdateAnimation(deltaTime);
	SetTextureVertex(uvArray, 4);
}


void Sprite::setCollision()
{
	onCollision = true;
}

bool Sprite::getCollision()
{
	return onCollision;
}

void Sprite::LoadTexture(const char * bmpFile) {
	TextureImporter::LoadBMP(bmpFile,texture);
	textureID = render->ChargeTexture(texture.width, texture.height, texture.data);
	
}


void Sprite::DrawMeshWithTexture(int typeDraw) {
	render->LoadIMatrix();
	render->SetWMatrix(WorldMatrix);

	if (material != NULL) {
		material->BindProgram();
		material->Bind("WVP");
		material->SetMatrixProperty(render->GetWVP());
	}

	render->BindTexture(textureID, uvBufferID);
	render->BeginDraw(0);
	render->BindBuffer(0, bufferId, 3);
	render->BeginDraw(1);
	render->BindBuffer(1, uvBufferID, 2);
	render->DrawBuffer(vertexCount, typeDraw);
	render->EndDraw(0);
	render->EndDraw(1);
}

void Sprite::Draw() {
	DrawMeshWithTexture(GL_TRIANGLE_STRIP);
}

Sprite::~Sprite() {
	render->DestroyBuffer(uvBufferID);
	delete[] vertex;
	delete[] uvArray;
}

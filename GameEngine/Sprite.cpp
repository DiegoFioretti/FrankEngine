#include "Sprite.h"

// Para dibujar con textura 
Sprite::Sprite(Renderer * render, int columns, int rows) : Shape(render) {
	onCollision = false;
	vertex = new float[12]{
		-1.0f, -1.0f, 0.f,
		-1.0f,  1.0f, 0.f,
		 1.0f, -1.0f, 0.f,
		 1.0f,  1.0f, 0.f
	};
	SetVertices(vertex, 4);

	anim = new Animation(columns, rows);
	
	uvArray = anim->UpdateAnimation(0);
	SetTextureVertex(uvArray, 4);
}

void Sprite::SetTextureVertex(float * vertices, int count) {
	DisposeTexture();

	uvVtxCount = count;
	ShouldDispouseTexture = true;
	uvBufferID = render->GenBuffer(vertices, sizeof(float)* count * 2);
}

void Sprite::DisposeTexture() {
	if (ShouldDispouseTexture)
	{
		render->DestroyBuffer(uvBufferID);
		ShouldDispouseTexture = false;
	}
}

void Sprite::SetAnim(int initF, int finishF, float timePerF) {
	anim->SetAnimation(initF, finishF, timePerF);
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

void Sprite::LoadMaterial(const char * bmpFile) {
	TextureImporter::LoadBMP(bmpFile,texture);
	textureID = render->ChargeTexture(texture.width, texture.height, texture.data);
	material->BindTexture("myTextureSampler");
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

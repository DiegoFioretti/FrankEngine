#include "Tile.h"


// Tile se encarga de manejar su textura propia 

Tile::Tile(int id)
{
	_id=id;
}

int Tile::getTileID()
{
	return _id;
}

void Tile::LoadTexture(const char* bmpFile) {
	TextureImporter::LoadBMP(bmpFile, texture);
	textureID = render->ChargeTexture(texture.width, texture.height, texture.data);
}

void Tile::UVArr(float* uv) {
	SetTextureVertex(uv, 4);
}

void Tile::SetTextureVertex(float* vertices, int count) {
	DisposeTexture();
	uvBufferID = render->GenBuffer(vertices, sizeof(float) * count * 2);
}

void Tile::DisposeTexture() {
	render->DestroyBuffer(uvBufferID);
}

void Tile::Draw() {
	DrawMeshWithTexture(GL_TRIANGLE_STRIP);
}

void Tile::DrawMeshWithTexture(int typeDraw) {
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

Tile::~Tile() {

}
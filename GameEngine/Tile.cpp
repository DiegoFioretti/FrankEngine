#include "Tile.h"

Tile::Tile(float x, float y, float z, int id, bool walk)
{
	_x = x;
	_y = y;
	_z = z;
	_id=id;
	_walkable = walk;
	//anim = new Animation(2, 2);
	//uvArray = anim->UpdateAnimation(0);
	SetTextureVertex(uvArray, 4);
}

void Tile::UVArr(float * uv) {
	SetTextureVertex(uv, 4);
}


void Tile::SetTextureVertex(float* vertices, int count) {
	DisposeTexture();

	ShouldDispouseTexture = true;
	uvBufferID = render->GenBuffer(vertices, sizeof(float) * count * 2);

}

void Tile::DisposeTexture() {
	if (ShouldDispouseTexture)
	{
		render->DestroyBuffer(uvBufferID);
		ShouldDispouseTexture = false;
	}
}


bool Tile::isWalkable() {
	return _walkable;
}

void Tile::setWalkable(bool walk) {
	_walkable = walk;
}

int Tile::getTileID()
{
	return _id;
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

void Tile::LoadTexture(const char* bmpFile) {
	TextureImporter::LoadBMP(bmpFile, texture);
	textureID = render->ChargeTexture(texture.width, texture.height, texture.data);
}
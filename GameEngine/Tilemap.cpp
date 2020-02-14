#include "Tilemap.h"



Tilemap::Tilemap(Renderer* render, Material* material, const char* bmpFile, int columns, int rows)
{
	pasto = new Tile(render, 1, 1);
	pasto->SetMaterial(material);
	pasto->LoadMaterial(bmpFile);
	pasto->SetPos(1, 6, 0);
	pasto->SetBoundingBox(2.0f, 2.0f);

	caja = new Tile(render, 1, 1);
	caja->SetMaterial(material);
	caja->LoadMaterial(bmpFile);
	caja->SetPos(4, 6, 0);
	caja->SetBoundingBox(2.0f, 2.0f);
}


Tilemap::~Tilemap()
{

}

void Tilemap::DrawTiles()
{
	pasto->Draw();
	caja->Draw();
}

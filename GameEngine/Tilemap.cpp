#include "Tilemap.h"



Tilemap::Tilemap(Renderer* render, Material* material, const char* bmpFile, int columns, int rows)
{
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			mapa[i][j] = new Tile(render, columns, rows);
			mapa[i][j]->SetMaterial(material);
			mapa[i][j]->LoadMaterial(bmpFile);
			mapa[i][j]->SetPos(1 + (2.0f * i), 1 + (2.0f * j), 0);
			mapa[i][j]->SetBoundingBox(2.0f, 2.0f);
			mapa[i][j]->SetAnim(0, 0, 0.0f);
		}
	}
	/*
	pasto = new Tile(render, columns, rows);
	pasto->SetMaterial(material);
	pasto->LoadMaterial(bmpFile);
	pasto->SetPos(1, 6, 0);
	pasto->SetBoundingBox(2.0f, 2.0f);
	pasto->SetAnim(0, 0, 0.0f);

	caja = new Tile(render, columns, rows);
	caja->SetMaterial(material);
	caja->LoadMaterial(bmpFile);
	caja->SetPos(4, 6, 0);
	caja->SetBoundingBox(2.0f, 2.0f);
	caja->SetAnim(2 ,2 , 0.5f);*/
}


Tilemap::~Tilemap()
{

}

void Tilemap::DrawTiles()
{
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			mapa[i][j]->Draw();
		}
	}
	//pasto->Draw();
	//caja->Draw();
}

void Tilemap::UpdateTilesAnim(float time)
{
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			mapa[i][j]->UpdAnim(time);
		}
	}
	//pasto->UpdAnim(time);
	//caja->UpdAnim(time);
}

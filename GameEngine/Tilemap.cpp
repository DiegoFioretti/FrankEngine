#include "Tilemap.h"



Tilemap::Tilemap(/*Renderer* render, Material* material, const char* bmpFile, int columns, int rows, */int x, int y, int z)
{
	_x = x;
	_y = y;
	_z = z;

	for (size_t i = 0; i < MAXTILES; i++)
	{
		_tileArchive[i] = NULL;
	}

	_tilesetExist = false;

	/*
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			mapa[i][j] = new Tile(render, columns, rows);
			mapa[i][j]->SetMaterial(material);
			mapa[i][j]->LoadMaterial(bmpFile);
			//mapa[i][j]->SetPos(x + (2.0f * i), y + (2.0f * j), z);
			mapa[i][j]->SetBoundingBox(2.0f, 2.0f);
			//mapa[i][j]->SetAnim(0, 0, 0.0f);
		}
	}*/
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

void Tilemap::loadBMPTileset(Renderer* render, Material* material, const char* bmpFile, int columns, int rows)
{

	_tileAmount = columns * rows;
	if (_tileAmount > MAXTILES)
	{
		printf("MAXIMO DE TILES ALCANZADO. CANCELANDO OPERACION");
	}
	else
	{
		int xCoord = 0;
		for (size_t i = 0; i < _tileAmount; i++)
		{
			_tileArchive[i] = new Tile(render, columns, rows, i);
			_tileArchive[i]->SetMaterial(material);
			_tileArchive[i]->LoadMaterial(bmpFile);
			_tileArchive[i]->SetBoundingBox(2.0f, 2.0f);
			_tileArchive[i]->SetAnim(i, i, 0.5f);
			xCoord++;
			/*if (xCoord >= columns)
			{
				xCoord = 0;
				yCoord++;
			}*/
		}

		_tileArchive[0]->SetPos(-3, 6, 0);
		_tileArchive[1]->SetPos(-1, 6, 0);
		_tileArchive[2]->SetPos(1, 6, 0);
		_tileArchive[3]->SetPos(3, 6, 0);

		_tilesetExist = true;
	}
}

void Tilemap::loatTXTTilemap(const char* txtFile, int width, int height)
{
	if (!_tilesetExist)
	{
		printf("ËRROR: No se puede cargar un mapa sin haber cargado un tileset anteriormente. Cancelando operacion");
	}
	else
	{
		_mapWidth = width;
		_mapHeight = height;
	//-------------------------------
	//leo el tilemap y lo guardo en un sting
		std::string tile;
		std::ifstream tileStream(txtFile, std::ios::in);
		if (tileStream.is_open()) {
			std::stringstream sstr;
			sstr << tileStream.rdbuf();
			tile = sstr.str();
			tileStream.close();
		}
		//Borro las cosas que no son numeros o comas
		tile.erase(std::remove(tile.begin(), tile.end(), 'D'), tile.end());
		tile.erase(std::remove(tile.begin(), tile.end(), 'a'), tile.end());
		tile.erase(std::remove(tile.begin(), tile.end(), 't'), tile.end());
		tile.erase(std::remove(tile.begin(), tile.end(), 'a'), tile.end());
		tile.erase(std::remove(tile.begin(), tile.end(), '{'), tile.end());
		tile.erase(std::remove(tile.begin(), tile.end(), '='), tile.end());
		tile.erase(std::remove(tile.begin(), tile.end(), '}'), tile.end());
		tile.erase(std::remove(tile.begin(), tile.end(), '    '), tile.end());
		tile.erase(std::remove(tile.begin(), tile.end(), ' '), tile.end());
		//paso el tring a un array de ints
		int num = 0;
		
		int mapa[MAXTILESINMAP];
		for (int i = 0; i < MAXTILESINMAP; i++)
		{
			mapa[i] = -1;
		}
		for (int i = 0; i < tile.length(); i++) {
			if (tile[i] == ',') {

			}
			else {
				mapa[num] = int(tile[i]) - 48;
				num++;
			}
		}
		
		for (size_t i = 0; i < MAXTILESINMAP; i++)
		{
			_mapGuide[i] = mapa[i];
		}

		//---------------------
	}
}

void Tilemap::DrawTiles()
{
	int num = 0;
	for (size_t i = 0; i < _mapWidth; i++)
	{
		for (size_t j = 0; j < _mapHeight; j++)
		{
			while (_mapGuide[num] < 0)
			{
				num++;
			}
			_tileArchive[_mapGuide[num]]->SetPos(_x + (2.0f * j), _y - (2.0f * i), _z);
			_tileArchive[_mapGuide[num]]->Draw();
			num++;
		}
	}
	/*_tileArchive[0]->Draw();
	_tileArchive[1]->Draw();
	_tileArchive[2]->Draw();
	_tileArchive[3]->Draw()¨;*/
	//pasto->Draw();
	//caja->Draw();
}

void Tilemap::UpdateTilesAnim(float time)
{
	int num = 0;
	for (size_t i = 0; i < _mapWidth; i++)
	{
		for (size_t j = 0; j < _mapHeight; j++)
		{
			while (_mapGuide[num] < 0)
			{
				num++;
			}
			_tileArchive[_mapGuide[num]]->UpdAnim(time);
			num++;
		}
	}
	/*
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			//mapa[i][j]->UpdAnim(time);
		}
	}
	_tileArchive[0]->UpdAnim(time);
	_tileArchive[1]->UpdAnim(time);
	_tileArchive[2]->UpdAnim(time);
	_tileArchive[3]->UpdAnim(time);*/
	//pasto->UpdAnim(time);
	//caja->UpdAnim(time);
}

#include "Tilemap.h"

Tilemap::Tilemap(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;

	for (size_t i = 0; i < MAXTILES; i++)
	{
		_tileArchive[i] = NULL;
	}
	for (size_t i = 0; i < MAXTILESINMAP; i++)
	{
		_mapGuide[i] = -1;
	}
	_tileAmount = 0;
	_tilesetExist = false;
}


Tilemap::~Tilemap()
{
	for (size_t i = 0; i < MAXTILES; i++)
	{
		if (_tileArchive[i] != NULL)
		{
			delete _tileArchive[i];
		}
	}
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
		for (size_t i = 0; i < _tileAmount; i++)
		{
			_tileArchive[i] = new Tile(render, columns, rows, i);
			_tileArchive[i]->SetMaterial(material);
			_tileArchive[i]->LoadMaterial(bmpFile);
			_tileArchive[i]->SetBoundingBox(2.0f, 2.0f);
			_tileArchive[i]->SetAnim(i, i, 0.5f);
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
		num = 0;
		
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
	num = 0;
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
}

void Tilemap::UpdateTilesAnim(float time)
{
	num = 0;
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
}

int Tilemap::GetTileAmount()
{
	return _tileAmount;
}

Tile* Tilemap::GetTileInfo(int tileid)
{
	if (tileid > 0 && tileid < MAXTILESINMAP)
	{
		return _tileArchive[tileid];
	}
	else
	{
		return NULL;
	}
}
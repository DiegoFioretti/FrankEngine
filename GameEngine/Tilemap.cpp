#include "Tilemap.h"

Tilemap::Tilemap(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
	 
	for (size_t i = 0; i < MAXTILESINMAP; i++)
	{
		_mapGuide[i] = -1;
	}
	_tileAmount = 0;
	_tilesetExist = false;
}


Tilemap::~Tilemap()
{
	
}

void Tilemap::loadBMPTileset(Material* material, const char* bmpFile, int columns, int rows)
{
	CutTileSet(columns, rows);
	_tileAmount = columns * rows;
	for (int i = 0; i < _tileAmount; i++){

		auxTile = new Tile(0,0,0,i,true);
		auxTile->SetMaterial(material);
		auxTile->LoadTexture(bmpFile);
		auxTile->SetBoundingBox(2.0f, 2.0f);
		auxTile->UVArr(GetTile(i));
		_tileArchive.push_back(auxTile);
		_tilesetExist = true;
	}
}

void Tilemap::CutTileSet(int col, int row) {

	uvVector = new vector<float*>();
	float frameW = 1.0f / col;
	float frameH = 1.0f / row;
	int totalSprites = col * row;

	for (int i = 0; i < totalSprites; i++) {
		float x = (i % col) * frameW;
		float y = (i / col) * frameH;

		uvArrays = new float[8]
		{
			 x , 1 - (y + frameH),
			 x , 1 - y ,
			(x + frameW) , 1 - (y + frameH),
			(x + frameW) , 1 - (y)
		};

		uvVector->push_back(uvArrays);
	}

}

float* Tilemap::GetTile(int index) {
	return uvVector->at(index);
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
		_tileAmount = _mapWidth * _mapHeight;
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
		
		//Arreglar esto para que cuando sea -38 pase abajo--------------
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

	//cout<<"x:" << _tileArchive[2]->GetPos().x <<"y: "<< _tileArchive[2]->GetPos().y<<"z: "<< _tileArchive[2]->GetPos().z<<endl;

	UpdateAnim();
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
			
			
			if (first)
			{
				pos.push_back(vec3(_x + (2.0f * j), _y - (2.0f * i), _z));
				totalTiles.push_back(_tileArchive[_mapGuide[num]]);
				totalTiles[_mapGuide[num]]->SetPos(_x + (2.0f * j), _y - (2.0f * i), _z);
				
			}
			_tileArchive[_mapGuide[num]]->Draw();
			num++;
			
		}
	}
	first = false;

}

void Tilemap::UpdateAnim() {

	for (int i = 0; i < _tileAmount; i++) {
		//_tileArchive[i]->UVArr();
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
			//_tileArchive[_mapGuide[num]]->UpdAnim(time);
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

void Tilemap::MakeColTile( Entity* A, int numTile ) {
	
	for (int i = 0; i < totalTiles.size(); i++)
	{
		if (totalTiles[i]->getTileID()==numTile)
		{
			//cout << i << "=" << totalTiles[i]->GetPos().x << " , "<< totalTiles[i]->GetPos().y << endl;
			col = new CollisionManager();
			tileCol.push_back(col);
			tileNum.push_back(i);
		}
	}
	for (int i = 0; i < tileCol.size(); i++)
	{
		totalTiles[tileNum[i]]->SetPos(pos[tileNum[i]].x, pos[tileNum[i]].y, pos[tileNum[i]].z);
		tileCol[i]->MakeCollision(A, totalTiles[tileNum[i]]);
	}
	
	Clean();
}

bool Tilemap::CheckColTile(int numTile, Entity* A) {

	return col->CheckCollision(_tileArchive[numTile], A);
}

void Tilemap::Clean() {


	tileCol.resize(0);
	tileNum.resize(0);
	//delete col;
}
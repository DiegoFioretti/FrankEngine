#include "Tilemap.h"

// Tilmap funciona de la siguiente manera:
// Se crean los tiles , se le setea el material, la textura , el bounding box y el uv uno x cada tile y se guardan en tileArchive
// Load TXT carga el txt y levanta todos los numeros asignados y los guarda en un array
// Draw lo que hace es agarrar los tiles creados, en este caso 4 y dibujarlos donde corresponden , y guarda la posicion de cada tile en un vec pos
// Col lo que hace es ver que numero le pasas (Num de Tile) ve la posicion y genera una colsion.
// Esta es la mejor y mas optima forma que creamos ya que solo usa solo 4 tiles para dibujar y con las posiciones que fueron dibujadas se puede crear la colision

Tilemap::Tilemap(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
	 
	for (size_t i = 0; i < MAXTILESINMAP; i++){
		_mapGuide[i] = -10;
	}
	_tilesetExist = false;
}



// cargado asignacion de textura para cada tile
void Tilemap::loadBMPTileset(Material* material, const char* bmpFile, int columns, int rows)
{
	CutTileSet(columns, rows);
	_tileAmount = columns * rows;
	for (int i = 0; i < _tileAmount; i++){

		auxTile = new Tile(i);
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

		uvArrays = new float[8]{

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
		
		for (int i = 0; i < tile.length(); i++)
		{
			if ((tile[i]-48)>-2)
			{
				_mapGuide[num] = int(tile[i]) - 48;
				num++;
			}
			
		}
	}
}

void Tilemap::DrawTiles(){
	num = 0;
	for (size_t i = 0; i < _mapWidth; i++){
		for (size_t j = 0; j < _mapHeight; j++){
			if (_mapGuide[num] < 0){

			}
			else
			{
				_tileArchive[_mapGuide[num]]->SetPos(_x + (2.0f * j), _y - (2.0f * i), _z);
				_tileArchive[_mapGuide[num]]->Draw();

				if (first){
					pos.push_back(vec3(_x + (2.0f * j), _y - (2.0f * i), _z));
				}
			}
			num++;
		}
	}
	first = false;
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

	if (!first)
	{
		for (int i = 0; i < _tileAmount; i++)
		{
			if (_mapGuide[i] == numTile)
			{
				_tileArchive[numTile]->SetPos(pos[i].x, pos[i].y, pos[i].z);
				cul->MakeCollision(A, _tileArchive[numTile]);
			}
		}
	}
}


Tilemap::~Tilemap()
{
	auxTile = NULL;
	_tileArchive.clear();
	delete uvVector;
}
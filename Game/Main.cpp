#include "Game.h"
#include <iostream>
using namespace std;
int main() 
{
	Game* game = new Game();

	if (game->Start(768,1024,(char*)&"Coso Engine!"))
	{
		game->Loop();
	}
	
	game->Stop();
	delete game;
	
	return 0;
}
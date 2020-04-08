#include "Game.h"
#include <iostream>
using namespace std;
int main() 
{
	Game* game = new Game();

	if (game->Start(600,800,(char*)&"THE FRANKENGINE LIVES ONCE AGAIN!"))
	{
		game->Loop();
	}
	
	game->Stop();
	delete game;
	
	return 0;
}
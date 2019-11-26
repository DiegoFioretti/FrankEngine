#include "Game.h"

int main() {
	Game* thisGame = new Game();

	thisGame->Init("Coso", 800, 600);

	thisGame->GameLoop();

	thisGame->Stop();
	return 0;
}
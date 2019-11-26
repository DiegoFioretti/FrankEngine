#include "BaseGame.h"

BaseGame::BaseGame()
{
}

BaseGame::~BaseGame()
{
}

bool BaseGame::Init(const char* name, int width, int height)
{
	gameWindow = new Window(name, width, height);

	gameRender = new Renderer();

	if (!gameRender->Init(gameWindow))
	{
		printf("No se pudo iniciar Renderer");
		return false;
	}

	return Start();
}

void BaseGame::GameLoop() 
{
	bool aux = true;

	while (!gameWindow->ShouldClose() && aux)
	{
		aux = Update();

		gameRender->SwapBuffers();

		gameWindow->PollEvents();
	}
}
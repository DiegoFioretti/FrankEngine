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

	gameRender->SetColor(0.0f, 0.0f, 0.4f, 1.0f);

	while (!gameWindow->ShouldClose() && aux)
	{
		aux = Update();

		gameRender->ClearScreen();

		Draw();

		gameRender->SwapBuffers();

		gameWindow->PollEvents();
	}
}
bool BaseGame::Stop()
{

	if (gameRender != NULL)
	{
		gameRender->Stop();

		delete gameRender;

		gameRender = NULL;
	}

	if (gameWindow != NULL)
	{
		gameWindow->Stop();

		delete gameWindow;

		gameWindow = NULL;
	}

	return true;
}
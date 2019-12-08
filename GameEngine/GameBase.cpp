#include "GameBase.h"

GameBase::GameBase() {

}
GameBase::~GameBase() {
}
bool GameBase::Start(int h, int w, char* name) {
	cout << "GameBase::Start()" << endl;

	window = new Window();
	if (!window->Start(w, h, name))
		return false;

	render = new Renderer();
	if (!render->Start(window))
		return false;
	render->setClearScreenColor(0.3f, 0.0f, 0.4f, 0.0f);
	render->ClearScreen();

	return OnStart();
}
void GameBase::Loop() {
	bool loop = true;
	while (loop && !window->ShouldClose()) {
		loop = OnUpdate();
		render->ClearScreen();
		OnDraw();
		render->SwapBuffer();
		window->PollEvents();
	}
}

bool GameBase::Stop() {
	cout << "GameBase::Stop()" << endl;
	OnStop();
	render->Stop();
	window->Stop();

	delete render;
	delete window;
	return true;
}


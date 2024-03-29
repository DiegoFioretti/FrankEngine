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

	render->setClearScreenColor(0.93f, 0.0f, 0.0f, 0.0f);

	render->ClearScreen();

	rnzr = new Renderizer(render);
	return OnStart();
}
void GameBase::Loop() {

	bool loop = true;
	while (loop && !window->ShouldClose()) {
		_currentFrame = glfwGetTime();
		_deltaTime = _currentFrame - _lastFrame;
		_lastFrame = _currentFrame;

		loop = OnUpdate();
		render->UpdateFrustum();
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

	delete rnzr;
	delete render;
	delete window;
	return true;
}

float GameBase::DeltaTime() {
	return _deltaTime;
}


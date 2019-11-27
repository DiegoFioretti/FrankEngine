#ifndef BASEGAME_H
#define BASEGAME_H
#pragma once

#include "Renderer.h"
#include "Window.h"

#define BASEGAMELIB __declspec(dllexport)

class BASEGAMELIB BaseGame
{
private:
	Window* gameWindow;
	Renderer* gameRender;
protected:
	virtual bool Start() = 0;
	virtual bool Stop() = 0;
	virtual bool Update() = 0;
	virtual void Draw() = 0;
public:
	BaseGame();
	~BaseGame();
	bool Init(const char* name, int width, int height);
	bool StopEngine();
	void GameLoop();
	bool GameStop();
};
#endif
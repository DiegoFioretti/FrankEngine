#pragma once
#include "Renderer.h"

class Renderizer
{
private:
	static Renderizer* Instance;
public:
	Renderer* rnd;
	static Renderizer* GetInstance();
	Renderizer(Renderer* render);
	mat4 MultiverseWolrdMatrix = mat4(1.0f);
	~Renderizer();
};


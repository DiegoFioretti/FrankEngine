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
	~Renderizer();
};


#include "Renderizer.h"



Renderizer::Renderizer(Renderer* render)
{
	rnd = render;
	Instance = this;
}

Renderizer* Renderizer::Instance = NULL;

Renderizer* Renderizer::GetInstance() {
	
	return Instance;
}

Renderizer::~Renderizer()
{
}

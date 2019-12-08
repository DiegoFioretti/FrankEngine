#pragma once
#include "Shape.h"
#include "Material.h"
class FRANKENGINE_API Triangle :public Shape
{

public:
	Triangle(Renderer *render);
	~Triangle();	
	void Draw() override;
};
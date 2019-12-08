#pragma once
#include "Entity.h"
#include "BoundingBox.h"
#include "Material.h"


class FRANKENGINE_API Shape : public Entity
{
protected:
	Material * material;

	bool shouldDispose;
	bool shouldDisposeColor;

	int vertexCount;
	int colorVertexCount;

	unsigned int colorBufferId;
	unsigned int bufferId;

	float * vertex;
	float * colorVertex;

public:
	Shape(Renderer * render);
	virtual void Draw() = 0;
	void DrawMesh(int typeDraw);
	void SetVertices(float * vertices, int count);
	void SetColorVertex(float * vertices, int count);
	void SetMaterial(Material* material);
	~Shape();
};


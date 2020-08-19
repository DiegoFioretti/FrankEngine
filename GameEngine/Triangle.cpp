#include "Triangle.h"
Triangle::Triangle() 
{
	
	vertex = new float[9]
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};
	
	//SetVertices(vertex, 3);

	colorVertex = new float[9]
	{
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f
	};

	SetColorVertex(colorVertex, 3);
}

Triangle::~Triangle()
{
	delete[] vertex;
	delete[] colorVertex;
}



void Triangle::Draw()
{
	DrawMesh(GL_TRIANGLES);
}



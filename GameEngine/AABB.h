#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Exports.h"
#include "Mesh.h"

class FRANKENGINE_API AABB : public Mesh {
public:
	AABB(Mesh msh);
	AABB();
	Bounds bounds;
	void CalculateBoundingBox(Bounds bounds);
	void CalculateBounds(vector<Vertex> vertices);
	void CalculateAllBounds(vector<Bounds> vertices);
	void RezBound(float x, float y, float z);
	void SetBox();
	void Setup();
	void DrawBox();
	vector<unsigned int> cIndices;
	Bounds bound;
	Bounds newBound;
	bool first = true;

	Bounds getBounds();
	Bounds getNewBounds();
	glm::vec3 getVertices(int a);

private:
	
	~AABB();
	glm::vec3 vertex[8];

};
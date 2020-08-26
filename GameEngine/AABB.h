#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>

#include <iostream>
#include <vector>
#include "Exports.h"
#include "Vertexx.h"

using namespace std;

struct Bounds
{
	float maxX = INT32_MIN;
	float maxY = INT32_MIN;
	float maxZ = INT32_MIN;
	float minX = INT32_MAX;
	float minY = INT32_MAX;
	float minZ = INT32_MAX;
};

class FRANKENGINE_API AABB {
public:
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
	void getAABB();

private:
	
	~AABB();
	unsigned int VAO, VBO, EBO;
	glm::vec3 vertex[8];

};
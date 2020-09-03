#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Transform.h"

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

class FRANKENGINE_API AABB : public Transform {
public:
	AABB();
	~AABB();
	Bounds bounds;
	void CalculateBoundingBox(Bounds bounds);
	void CalculateBounds(vector<Vertex> vertices);
	void CalculateAllBounds(vector<Bounds> vertices);
	void SetBox();
	void Setup();
	void DrawBox();
	vector<unsigned int> cIndices;
	Bounds bound;
	Bounds newBound;
	bool first = true;

	Bounds getBounds();
	Bounds getNewBounds();
	glm::vec3* getVertexPointer();
	void getAABB();

private:
	unsigned int VAO, VBO, EBO;
	glm::vec3 vertex[8];
	glm::vec3* auxPointer;

};
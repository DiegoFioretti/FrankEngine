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
	Bounds bounds;
	void CalculateBoundingBox(Bounds bounds);
	void CalculateBounds(vector<Vertex> vertices);
	void SetBox();
	void Setup();
	void DrawBox(Lighting shader);
	

private:
	
	~AABB();
	glm::vec3 vertex[8];

};
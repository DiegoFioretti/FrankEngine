#include "AABB.h"


AABB::AABB() {
	auxPointer = vertex;
}

AABB::~AABB() {

}

void AABB::SetBox() {

	GLushort cubeIndices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	for (int i = 0; i < 36; i++)
		cIndices.push_back(cubeIndices[i]);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	Setup();

}

void AABB::Setup()
{
	

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cIndices.size() * sizeof(unsigned int), &cIndices[0], GL_DYNAMIC_DRAW);

	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);

	
}

void AABB::CalculateBounds(vector<Vertex> vertices)
{
	if (!vertices.empty())
	{
		Bounds resetBounds;
		bounds = resetBounds;
		for (int i = 0; i < vertices.size(); i++)
		{
			if (vertices[i].Position.x < bounds.minX)
				bounds.minX = vertices[i].Position.x;
			if (vertices[i].Position.x > bounds.maxX)
				bounds.maxX = vertices[i].Position.x;
			if (vertices[i].Position.y < bounds.minY)
				bounds.minY = vertices[i].Position.y;
			if (vertices[i].Position.y > bounds.maxY)
				bounds.maxY = vertices[i].Position.y;
			if (vertices[i].Position.z < bounds.minZ)
				bounds.minZ = vertices[i].Position.z;
			if (vertices[i].Position.z > bounds.maxZ)
				bounds.maxZ = vertices[i].Position.z;
		}
	}

	CalculateBoundingBox(bounds);
}

void AABB::CalculateAllBounds(vector<Bounds> allBounds)
{
		Bounds resetBounds;
		bounds = resetBounds;
		for (int i = 0; i < allBounds.size(); i++)
		{
			if (allBounds[i].maxX > bounds.maxX)
				bounds.maxX = allBounds[i].maxX;

			if (allBounds[i].minX < bounds.minX)
				bounds.minX = allBounds[i].minX;

			if (allBounds[i].maxY > bounds.maxY)
				bounds.maxY = allBounds[i].maxY;

			if (allBounds[i].minY < bounds.minY)
				bounds.minY = allBounds[i].minY;

			if (allBounds[i].maxZ > bounds.maxZ)
				bounds.maxZ = allBounds[i].maxZ;

			if (allBounds[i].minZ < bounds.minZ)
				bounds.minZ = allBounds[i].minZ;
			
		}

	CalculateBoundingBox(bounds);
}

void AABB::CalculateBoundingBox(Bounds bounds)
{
	bound = bounds;
	glm::vec3 boundingBoxVertex[8] =
	{
		glm::vec3(bounds.minX, bounds.minY, bounds.maxZ),
		glm::vec3(bounds.maxX, bounds.minY, bounds.maxZ),
		glm::vec3(bounds.maxX, bounds.maxY, bounds.maxZ),
		glm::vec3(bounds.minX, bounds.maxY, bounds.maxZ),
		glm::vec3(bounds.minX, bounds.minY, bounds.minZ),
		glm::vec3(bounds.maxX, bounds.minY, bounds.minZ),
		glm::vec3(bounds.maxX, bounds.maxY, bounds.minZ),
		glm::vec3(bounds.minX, bounds.maxY, bounds.minZ),
	};

	for (int i = 0; i < 8; i++)
		vertex[i] = WorldMatrix * glm::vec4(boundingBoxVertex[i], 1.f);

	Setup();
}

glm::vec3* AABB::getVertexPointer() 
{
	return auxPointer;
}

void AABB::DrawBox(){
	
	//shader.use();
	glBindVertexArray(VAO);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBindVertexArray(0);

}

void AABB::getAABB() {

	cout << " MaxX: " << bounds.maxX << endl;
	cout << " MaxY: " << bounds.maxY << endl;
	cout << " MaxZ: " << bounds.maxZ << endl;

}

Bounds AABB::getBounds() {
	return bound;
}

Bounds AABB::getNewBounds() {
	if (first)
	{
		newBound = bound;
		first = false;
	}
	return newBound;
}
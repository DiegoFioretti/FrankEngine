#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "Exports.h"
#include "Shader3D.h"
#include "Lighting.h"
#include "Vertexx.h"

using namespace std;


struct Texture {
	unsigned int id;
	string type;
	string path;
};



class FRANKENGINE_API Mesh
{
protected:
	int GetVAO();
	int GetVBO();
	int GetEBO();
	vector<unsigned int> GetIndices();

public:
	int layer;
	/*  Mesh Data  */
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	/*  Functions  */
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, int layer);
	Mesh();
	void Draw(Shader3D shader);
	void Draw(Lighting shader);
	unsigned int VAO, VBO, EBO;
	
	~Mesh();
private:

	/*  Functions    */
	void setupMesh();

};




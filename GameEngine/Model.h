#pragma once

#include "Exports.h"
#include "Mesh.h"
#include "Transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <list>
using namespace std;

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

struct children {
	string name;
	Transform* trans;
	Mesh meshes;

};

class FRANKENGINE_API Model : public Transform
{
public:
	/*  Model Data */
	vector <Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	vector <Mesh> meshes;
	vector <string> names;
	vector <children> child;
	Transform * tempT;
	int currentLayer;
	string directory;
	bool gammaCorrection;
	/*  Functions   */

	Model(string const& path, bool gamma = false);
	void Draw(Shader3D shader);
	void Draw(Lighting shader);
	~Model();
	void MoveChilden(string namea);
	void SetScale(vec3 newScale);
	void SetPos(vec3 newPos);
	void SetRot(vec3 newRot);

private:
	// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
	void loadModel(string const& path);
	// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void processNode(aiNode* node, const aiScene* scene);

	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	// checks all material textures of a given type and loads the textures if they're not loaded yet.
	// the required info is returned as a Texture struct.
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

};






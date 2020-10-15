#pragma once

#include "Exports.h"
#include "Mesh.h"
#include "AABB.h"

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

struct Node {
	string name;
	Mesh meshes;
	AABB* aabb;
	Node *hijo= nullptr;
};

class FRANKENGINE_API Model : public AABB
{
public:
	/*  Model Data */
	vector <Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	vector <Mesh> meshes;
	vector <string> names;
	vector <Node> child;
	vector <Bounds> allBounds;
	Transform * tempT;
	AABB* tempAABB;

	Bounds bon;

	//AABB* totalAABB;
	Mesh* tempMesh;
	vector<vector<Vertex>> *verticesTemp;
	vector<unsigned int> indicesTemp;
	vector<Texture> texturesTemp;

	int currentLayer;
	string directory;
	bool gammaCorrection;
	bool first = false;
	/*  Functions   */

	Model(string const& path);
	void Draw(Shader3D shader);
	void Draw(Lighting shader);
	~Model();

	void MoveChildren(string namea,float x , float y,float z);
	void MoveAllChildren(string namea, float x, float y, float z);
	void RotChildren(string namea, float x, float y, float z);
	void ScaleChildren(string namea, vec3 num);
	void Rotate(float x, float y, float z);
	void SetScaleChilden(vec3 newScale);
	void SetPosM(vec3 newPos);
	void SetRot(vec3 newRot);
	void MTranslate(float x, float y, float z);
	void GetNames();
	void AllSons();
	void GetChildPos(int num);
	void Db_CheckIfInFrustrum();
	int sonsR;
	mat4 MultiverseWorld = mat4(1.0);

private:
	// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
	void loadModel(string const& path);
	// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void processNode(aiNode* node, const aiScene* scene);

	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	Bounds GenerateBounds(vec3 v[], mat4 mat);
	Bounds GenerateBoundsByVertex(vec3 v[]);

	glm::mat4 AssimpTransformToGlm(aiMatrix4x4* from);
	//bool AABBInFrustrum(AABB* box);
	// checks all material textures of a given type and loads the textures if they're not loaded yet.
	// the required info is returned as a Texture struct.
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

};






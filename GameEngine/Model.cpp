#include "Model.h"
#define STB_IMAGE_IMPLEMENTATION   
#include "stb_image.h"


// constructor, expects a filepath to a 3D model.
Model::Model(string const& path){
	this->GetPos();
	loadModel(path);
}
// draws the model, and thus all its meshes
void Model::Draw(Shader3D shader){
	for (unsigned int i = 0; i < child.size(); i++) {
		shader.setMat4("model",child[i].aabb->GetWorldMatrix());
		//child[i].aabb->Draw(shader);
	}
}

void Model::Draw(Lighting shader){

		for (unsigned int i = 0; i < child.size(); i++) {
				shader.modelLight(child[i].aabb->GetWorldMatrix());
				child[i].meshes.Draw(shader);
				child[i].aabb->DrawBox();
		}
		//this->DrawBox();
}

void Model::Db_CheckIfInFrustrum() 
{
	//cout << "0 / 0 " << render->MainCamera()->frustum[0][0] << endl;
	/*if (render->PointInFrustum(this->GetPos()))
	{
		cout << " model is in frustrum." << endl;
	}
	else
	{
		cout << " model is not in frustrum." << endl;
	}
	
	for (unsigned int i = 0; i < child.size(); i++) 
	{
		if (render->PointInFrustum(child[i].aabb->GetPos()))
			cout << child[i].name << " is in frustrum." << endl;
		else
			cout << child[i].name << " is not in frustrum." << endl;
	}*/

	for (unsigned int i = 0; i < child.size(); i++)
	{
		cout << "-----------------------" << endl;
		cout << child[i].name << endl;
		child[i].aabb->getAABB();
	}
}

// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
void Model::loadModel(string const& path)
{
	// read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return;
	}
	// retrieve the directory path of the filepath
	directory = path.substr(0, path.find_last_of('/'));

	// process ASSIMP's root node recursively
	processNode(scene->mRootNode, scene);

	//---- test
	list<int> meshesLayers;

	for (int i = 0; i < meshes.size(); i++)
	{
		meshesLayers.push_back(meshes[i].layer);
	}

	meshesLayers.sort();
	meshesLayers.unique();

	int newValue = 0;
	int newLayerValue = 1;

	for (std::list<int>::iterator it = meshesLayers.begin(); it != meshesLayers.end(); it++)
	{
		newValue = *it;

		for (int j = 0; j < meshes.size(); j++)
		{
			if (meshes[j].layer == newValue)
			{
				meshes[j].layer = newLayerValue;
			}
		}

		newLayerValue++;
	}
	//--- hasta aca

	if (child[0].name == "padre")
	{
		allBounds.clear();
		for (size_t i = 0; i < child.size(); i++)
		{
			allBounds.push_back(child[i].aabb->getBounds());
		}
		this->CalculateAllBounds(allBounds);
	}
	
	for (size_t i = 0; i < child.size()-1; i++)
	{
		child[i].hijo = &child[i + 1];
	}
}

// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
void Model::processNode(aiNode * node, const aiScene * scene){

	// process each mesh located at the current node
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		// the node object only contains indices to index the actual objects in the scene. 
		// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		string name = node->mName.C_Str();
		cout << name << " loaded." << endl;
		//node->mTransformation.
			
		tempAABB = new AABB();
		tempAABB->SetBox();
		tempAABB->CalculateBounds(processMesh(mesh, scene).vertices);

		Node hijo = { name, processMesh(mesh, scene), tempAABB};
		vec3 sonPos;
		for (size_t i = 0; i < hijo.meshes.vertices.size(); i++)
		{
			sonPos += hijo.meshes.vertices[i].Position;
		}
		sonPos.x = sonPos.x / hijo.meshes.vertices.size();
		sonPos.y = sonPos.y / hijo.meshes.vertices.size();
		sonPos.z = sonPos.z / hijo.meshes.vertices.size();

		hijo.aabb->SetPos(sonPos);
		hijo.aabb->SetWorldMatrix(hijo.aabb->GetWorldMatrix() * this->GetWorldMatrix());

		//hijo
		child.push_back(hijo);
		if (node->mNumChildren > 0) {
			child[child.size()-1].hijo = &child[child.size()];
		}
		//cout << name << endl;
	}
	int a = node->mNumChildren;
	// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		currentLayer++; // Separar los nodos en distintas capas.
		processNode(node->mChildren[i], scene);
		currentLayer--;
	}
	
}

glm::mat4 Model::AssimpTransformToGlm(aiMatrix4x4* from)
{
	glm::mat4 to;

	to[0][0] = (float)from->a1; to[0][1] = (float)from->b1;  to[0][2] = (float)from->c1; to[0][3] = (float)from->d1;
	to[1][0] = (float)from->a2; to[1][1] = (float)from->b2;  to[1][2] = (float)from->c2; to[1][3] = (float)from->d2;
	to[2][0] = (float)from->a3; to[2][1] = (float)from->b3;  to[2][2] = (float)from->c3; to[2][3] = (float)from->d3;
	to[3][0] = (float)from->a4; to[3][1] = (float)from->b4;  to[3][2] = (float)from->c4; to[3][3] = (float)from->d4;

	return to;
}

Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	// data to fill
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	
	// Walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{

		Vertex vertex;
		glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
		// positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		// normals
		if (mesh->HasNormals()){
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
		}
		
		// texture coordinates
		if (mesh->HasTextureCoords(0)) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else {
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}

		if (mesh->HasTangentsAndBitangents())
		{
			// tangent
			vector.x = mesh->mTangents[i].x;
			vector.y = mesh->mTangents[i].y;
			vector.z = mesh->mTangents[i].z;
			vertex.Tangent = vector;
			// bitangent
			vector.x = mesh->mBitangents[i].x;
			vector.y = mesh->mBitangents[i].y;
			vector.z = mesh->mBitangents[i].z;
			vertex.Bitangent = vector;
		}
		
		vertices.push_back(vertex);
	}

	// now wak through each of the mesh's faces (a face is a mesh its triangle)
	// and retrieve the corresponding vertex indices.
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
	// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
	// Same applies to other texture as the following list summarizes:
	// diffuse: texture_diffuseN
	// specular: texture_specularN
	// normal: texture_normalN

	// 1. diffuse maps
	vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. specular maps
	vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// 3. normal maps
	std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4. height maps
	std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	// return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices, textures,currentLayer);
} 

// checks all material textures of a given type and loads the textures if they're not loaded yet.
// the required info is returned as a Texture struct.
vector<Texture> Model::loadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;

		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true; // a texture with the same filepath has already been loaded, 
							 //continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if texture hasn't been loaded already, load it
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), this->directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture);  
			// store it as texture loaded for entire model, to ensure we won't unnecesery 
			// load duplicate textures.
		}
	}
	return textures;
}

// Esto es para cargar la textura  :)
unsigned int TextureFromFile(const char* path, const string & directory, bool gamma)
{
	string filename = string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
/*
bool Model::AABBInFrustrum(AABB* box) {
	for (int p= 0; p < 6; p++)
	{
		if (render->MainCamera()->frustum[p][0] * box->bounds.minX + render->MainCamera()->frustum[p][1] * box->bounds.minY + render->MainCamera()->frustum[p][2] * box->bounds.minZ + render->MainCamera()->frustum[p][3] > 0)
			continue;
		if (render->MainCamera()->frustum[p][0] * box->bounds.maxX + render->MainCamera()->frustum[p][1] * box->bounds.minY + render->MainCamera()->frustum[p][2] * box->bounds.minZ + render->MainCamera()->frustum[p][3] > 0)
			continue;
		if (render->MainCamera()->frustum[p][0] * box->bounds.minX + render->MainCamera()->frustum[p][1] * box->bounds.maxY + render->MainCamera()->frustum[p][2] * box->bounds.minZ + render->MainCamera()->frustum[p][3] > 0)
			continue;
		if (render->MainCamera()->frustum[p][0] * box->bounds.maxX + render->MainCamera()->frustum[p][1] * box->bounds.maxY + render->MainCamera()->frustum[p][2] * box->bounds.minZ + render->MainCamera()->frustum[p][3] > 0)
			continue;
		if (render->MainCamera()->frustum[p][0] * box->bounds.minX + render->MainCamera()->frustum[p][1] * box->bounds.minY + render->MainCamera()->frustum[p][2] * box->bounds.maxZ + render->MainCamera()->frustum[p][3] > 0)
			continue;
		if (render->MainCamera()->frustum[p][0] * box->bounds.maxX + render->MainCamera()->frustum[p][1] * box->bounds.minY + render->MainCamera()->frustum[p][2] * box->bounds.maxZ + render->MainCamera()->frustum[p][3] > 0)
			continue;
		if (render->MainCamera()->frustum[p][0] * box->bounds.minX + render->MainCamera()->frustum[p][1] * box->bounds.maxY + render->MainCamera()->frustum[p][2] * box->bounds.maxZ + render->MainCamera()->frustum[p][3] > 0)
			continue;
		if (render->MainCamera()->frustum[p][0] * box->bounds.maxX + render->MainCamera()->frustum[p][1] * box->bounds.maxY + render->MainCamera()->frustum[p][2] * box->bounds.maxZ + render->MainCamera()->frustum[p][3] > 0)
			continue;
		return false;
	}
	return true;
}
*/
//-----------------------------------TRANSFORMACIONES--------------------------------------
Bounds Model::GenerateBounds(vec3 v[], mat4 mat)
{
	vec3 v2[8];
	for (int i = 0; i < 8; i++)
	{
		v2[i] = mat * vec4(v[i], 1.f);
	}

	return GenerateBoundsByVertex(v2);
}

Bounds Model::GenerateBoundsByVertex(vec3 v[])
{
	Bounds returnBounds;
	for (int i = 0; i < 8; i++)
	{
		returnBounds.minX = v[i].x < returnBounds.minX ? v[i].x : returnBounds.minX;
		returnBounds.minY = v[i].y < returnBounds.minY ? v[i].y : returnBounds.minY;
		returnBounds.minZ = v[i].z < returnBounds.minZ ? v[i].z : returnBounds.minZ;
		returnBounds.maxX = v[i].x > returnBounds.maxX ? v[i].x : returnBounds.maxX;
		returnBounds.maxY = v[i].y > returnBounds.maxY ? v[i].y : returnBounds.maxY;
		returnBounds.maxZ = v[i].z > returnBounds.maxZ ? v[i].z : returnBounds.maxZ;
	}
	return returnBounds;
}

//					de todo el modelo
void Model::SetScaleChilden(vec3 newScale)
{
	this->SetScale(newScale);
	for (size_t i = 0; i < child.size(); i++){
		child[i].aabb->SetScaleChild(newScale, this->GetWorldMatrix());
		//bon = GenerateBounds(child[i].aabb->boxVertex, GetWorldMatrix());
		//child[i].aabb->GenerateBoundingBox(bon);
	}
}
void Model::SetPosM(vec3 newPos){
	
	this->SetPos(newPos);
	for (size_t i = 0; i < child.size(); i++){
		child[i].aabb->SetPosChild(newPos,this->GetWorldMatrix());
		//bon = GenerateBounds(child[i].aabb->boxVertex, GetWorldMatrix());
		//child[i].aabb->GenerateBoundingBox(bon);
	}
}

void Model::SetRot(vec3 newRot)
{
	for (size_t i = 0; i < child.size(); i++)
	{
		child[i].aabb->SetRot(newRot);
	}
}

void Model::MTranslate(float x, float y, float z) {
	this->Translate(x, y, z);
	for (size_t i = 0; i < child.size(); i++)
	{
		child[i].aabb->TranslateChildren(x, y, z, this->GetWorldMatrix());
		MultiverseWorld = this->GetWorldMatrix() * child[i].aabb->GetWorldMatrix();
	}
}

void Model::Rotate(float x, float y, float z)
{
	for (size_t i = 0; i < child.size(); i++)
	{
		child[i].aabb->Rotate(x, y, z);
	}
}

//					del hijo y sus hijos
void Model::MoveAllChildren(string namea, float x, float y, float z) {

	sonsR = 0;
	for (size_t i = 0; i < child.size(); i++) {
		if (child[i].name == namea) {
			child[i].aabb->Translate(0.1, 0, 0);
			sonsR = i;
			AllSons();
		}
	}

	if (child[0].name == "padre")
	{
		allBounds.clear();
		for (size_t i = 0; i < child.size(); i++)
		{
			allBounds.push_back(child[i].aabb->getNewBounds());
		}
		child[0].aabb->CalculateAllBounds(allBounds);
	}
}

void Model::AllSons() {
	if (child[sonsR].hijo != nullptr){
		child[sonsR].hijo->aabb->Translate(0.1, 0, 0);
		sonsR++;
		AllSons();
	}
}

void Model::GetChildPos(int num)
{
	cout << child[num].name << " X: " << child[num].aabb->GetPos().x << endl;
	cout << child[num].name << " Y: " << child[num].aabb->GetPos().y << endl;
	cout << child[num].name << " Z: " << child[num].aabb->GetPos().z << endl;
}

//						mueve solo un hijo
void Model::ScaleChildren(string namea, vec3 num){
	for (size_t i = 0; i < child.size(); i++) {
		if (child[i].name == namea) {
			child[i].aabb->SetScale(num);
		}
	}
}
void Model::RotChildren(string namea, float x, float y, float z) {
	for (size_t i = 0; i < child.size(); i++) {
		if (child[i].name == namea) {
			child[i].aabb->Rotate(x, y, z);
		}
	}
}

void Model::MoveChildren(string namea, float x, float y, float z) {
	for (size_t i = 0; i < child.size(); i++) {
		if (child[i].name == namea) {
			child[i].aabb->TranslateChildren(x,y,z, this->GetWorldMatrix());
			MultiverseWorld = this->GetWorldMatrix() * child[i].aabb->GetWorldMatrix();
		}
	}
}

// Devuelve todos los nombres del modelo
void Model::GetNames() {
	for (size_t i = 0; i < child.size(); i++) {
		cout << i << ": " <<endl;
		child[i].aabb->getAABB();
	}
}

Model::~Model()
{
}


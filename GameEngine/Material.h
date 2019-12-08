#pragma once
#include "Exports.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
using namespace std;
class FRANKENGINE_API Material
{
	unsigned int ProgramID;
	unsigned int matrixID;
	unsigned int textureId;

public:
	Material();
	~Material();
	unsigned int  LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	void Bind(const char* name);
	void SetMatrixProperty(mat4& mat);
	void BindTexture(const char* name);
	void BindProgram();
};


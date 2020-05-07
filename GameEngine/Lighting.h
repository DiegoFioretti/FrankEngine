#pragma once
#include "Exports.h"
#include "Shader3D.h"
#include <iostream>

class FRANKENGINE_API Lighting
{
public:
	unsigned int ID;

	Lighting(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	void use();
	void position(glm::vec3 pos);
	void viewPosition(glm::vec3 pos);
	void lightPropierties(std::string name);
	void lightPropierties(glm::vec3 lightColor, float difCulor, float ambientColor, glm::vec3 specular);
	void materialPropierties(std::string name);
	void materialPropierties(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shiness);
	void viewProyection(glm::mat4 view, glm::mat4 proy);
	void modelLight(glm::mat4 model);

	~Lighting();
private:
	Shader3D* newShader;


};


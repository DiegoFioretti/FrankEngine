#pragma once
#include "Exports.h"
#include "Shader3D.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <regex>
#include <string>
using std::string;

class FRANKENGINE_API Lighting
{
public:
	unsigned int ID;
	int i = 0;
	Lighting(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	void use();
	void position(glm::vec3 pos);
	void viewPosition(glm::vec3 pos);
	void ambientPropierties(std::string name);
	void ambientPropierties(glm::vec3 lightColor, float difCulor, float ambientColor, glm::vec3 specular);
	void directionalPropierties(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	void pointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);
	void spotLight(std::string name, glm::vec3 position, glm::vec3 direction);
	void spotLight(glm::vec3 position, glm::vec3 direction,glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic,float cutOff,float outerCutOff);
	void materialPropierties(std::string name);
	void materialPropierties(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shiness);
	void materialShiness(float shiness);

	void viewProyection(glm::mat4 view, glm::mat4 proy);
	void modelLight(glm::mat4 model);

	~Lighting();
private:
	Shader3D* newShader;
	string automaticSetPointLights(int i, int j);
	

};


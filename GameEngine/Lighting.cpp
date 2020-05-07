#include "Lighting.h"



Lighting::Lighting(const char* vertexPath, const char* fragmentPath, const char* geometryPath ){
	
	newShader = new Shader3D(vertexPath, fragmentPath, geometryPath);

}

void Lighting::use() {
	newShader->use();
}

void Lighting::position(glm::vec3 pos) {
	newShader->setVec3("light.position", pos);
}

void Lighting::viewPosition(glm::vec3 pos) {
	newShader->setVec3("viewPos", pos);
}

void Lighting::lightPropierties(std::string name) {
	if (name == "base")
	{
		glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.65f); // decrease the influence
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.7f); // low influence
		newShader->setVec3("light.ambient", ambientColor);
		newShader->setVec3("light.diffuse", diffuseColor);
		newShader->setVec3("light.specular", 0.5f, 0.5f, 0.5f);
	}

}

void Lighting::lightPropierties(glm::vec3 lColor, float difCulor, float aColor, glm::vec3 specular) {

	glm::vec3 lightColor(lColor);
	glm::vec3 diffuseColor = lightColor * glm::vec3(difCulor); // decrease the influence
	glm::vec3 ambientColor = diffuseColor * glm::vec3(aColor); // low influence
	newShader->setVec3("light.ambient", ambientColor);
	newShader->setVec3("light.diffuse", diffuseColor);
	newShader->setVec3("light.specular", specular);
}

void Lighting::materialPropierties(std::string name) {
	glm::vec3 mAmient(1.0f, 1.0f, 1.0f);
	glm::vec3 mDiffuse(1.0f, 1.0f, 1.0f);
	glm::vec3 mSpecular(1.0f, 1.0f, 1.0f);
	float shininess=1.0f;

	if (name=="base")
	{
		
		mAmient= glm::vec3(1.0f, 1.0f, 1.0f);
		mDiffuse= glm::vec3(1.0f, 1.0f, 1.0f);
		mSpecular=glm::vec3(1.0f, 1.0f, 1.0f);
		shininess=1.0f;
	}

	if (name == "emerald")
	{
		mAmient = glm::vec3(0.0215f, 0.1745f, 0.0215f);
		mDiffuse = glm::vec3(0.07568f, 0.61424f, 0.07568f);
		mSpecular = glm::vec3(0.633f, 0.727811f, 0.633f);
		shininess = 0.6f;
	}

	if (name == "jade")
	{
		mAmient = glm::vec3(0.135f, 0.2225f, 0.1575f);
		mDiffuse = glm::vec3(0.54f, 0.89f, 0.63f);
		mSpecular = glm::vec3(0.316228f, 0.316228f, 0.316228f);
		shininess = 0.1f;
	}

	if (name == "obsidian")
	{
		mAmient = glm::vec3(0.05375f, 0.05f, 0.06625f);
		mDiffuse = glm::vec3(0.18275f, 0.17f, 0.22525f);
		mSpecular = glm::vec3(0.332741f, 0.328634f, 0.346435f);
		shininess = 0.3f;
	}

	if (name == "pearl")
	{
		mAmient = glm::vec3(0.25f, 0.20725f, 0.20725f);
		mDiffuse = glm::vec3(1.0f, 0.829f, 0.829f);
		mSpecular = glm::vec3(0.296648f, 0.296648f, 0.296648f);
		shininess = 0.088f;
	}

	if (name == "ruby")
	{
		mAmient = glm::vec3(0.1745f, 0.01175f, 0.01175f);
		mDiffuse = glm::vec3(0.61424f, 0.04136f, 0.04136f);
		mSpecular = glm::vec3(0.727811f, 0.626959f, 0.626959f);
		shininess = 0.6f;
	}

	if (name == "turquoise")
	{
		mAmient = glm::vec3(0.1f, 0.18725f, 0.1745f);
		mDiffuse = glm::vec3(0.396f, 0.74151f, 0.69102f);
		mSpecular = glm::vec3(0.297254f, 0.30829f, 0.306678f);
		shininess = 0.1f;
	}

	if (name == "brass")
	{
		mAmient = glm::vec3(0.329412f, 0.223529f, 0.027451f);
		mDiffuse = glm::vec3(0.780392f, 0.568627f, 0.113725f);
		mSpecular = glm::vec3(0.992157f, 0.941176f, 0.807843f);
		shininess = 0.21794872f;
	}

	if (name == "bronze")
	{
		mAmient = glm::vec3(0.2125f, 0.1275f, 0.054f);
		mDiffuse = glm::vec3(0.714f, 0.4284f, 0.18144f);
		mSpecular = glm::vec3(0.393548f, 0.271906f, 0.166721f);
		shininess = 0.2f;
	}

	if (name == "chrome")
	{
		mAmient = glm::vec3(0.25f, 0.25f, 0.25f);
		mDiffuse = glm::vec3(0.4f, 0.4f, 0.4f);
		mSpecular = glm::vec3(0.774597f, 0.774597f, 0.774597f);
		shininess = 0.6f;
	}

	if (name == "copper")
	{
		mAmient = glm::vec3(0.19125f, 0.0735f, 0.0225f);
		mDiffuse = glm::vec3(0.7038f, 0.27048f, 0.0828f);
		mSpecular = glm::vec3(0.256777f, 0.137622f, 0.086014f);
		shininess = 0.1f;
	}

	if (name == "gold")
	{
		mAmient = glm::vec3(0.24725f, 0.1995f, 0.0745f);
		mDiffuse = glm::vec3(0.75164f, 0.60648f, 0.22648f);
		mSpecular = glm::vec3(0.628281f, 0.555802f, 0.366065f);
		shininess = 0.4f;
	}

	if (name == "silver")
	{
		mAmient = glm::vec3(0.19225f, 0.19225f, 0.19225f);
		mDiffuse = glm::vec3(0.50754f, 0.50754f, 0.50754f);
		mSpecular = glm::vec3(0.508273f, 0.508273f, 0.508273f);
		shininess = 0.4f;
	}

	if (name == "black plastic")
	{
		mAmient = glm::vec3(0.0f, 0.0f, 0.0f);
		mDiffuse = glm::vec3(0.01f, 0.01f, 0.01f);
		mSpecular = glm::vec3(0.50f, 0.50f, 0.50f);
		shininess = 0.25f;
	}

	if (name == "cyan plastic")
	{
		mAmient = glm::vec3(0.0f, 0.1f, 0.06f);
		mDiffuse = glm::vec3(0.0f, 0.50980392f, 0.50980392f);
		mSpecular = glm::vec3(0.50196078f, 0.50196078f, 0.50196078f);
		shininess = 0.25f;
	}

	if (name == "green plastic")
	{
		mAmient = glm::vec3(0.0f, 0.0f, 0.0);
		mDiffuse = glm::vec3(0.1f, 0.35f, 0.1f);
		mSpecular = glm::vec3(0.45f, 0.55f, 0.45f);
		shininess = 0.25f;
	}

	if (name == "red plastic")
	{
		mAmient = glm::vec3(0.0f, 0.0f, 0.0);
		mDiffuse = glm::vec3(0.5f, 0.0f, 0.0f);
		mSpecular = glm::vec3(0.7f, 0.6f, 0.6f);
		shininess = 0.25f;
	}

	if (name == "white plastic")
	{
		mAmient = glm::vec3(0.0f, 0.0f, 0.0);
		mDiffuse = glm::vec3(0.55f, 0.55f, 0.55f);
		mSpecular = glm::vec3(0.70f, 0.70f, 0.70f);
		shininess = 0.25f;
	}

	if (name == "yellow plastic")
	{
		mAmient = glm::vec3(0.0f, 0.0f, 0.0);
		mDiffuse = glm::vec3(0.5f, 0.5f, 0.0f);
		mSpecular = glm::vec3(0.60f, 0.60f, 0.50f);
		shininess = 0.25f;
	}

	if (name == "black rubber")
	{
		mAmient = glm::vec3(0.02f, 0.02f, 0.02f);
		mDiffuse = glm::vec3(0.01f, 0.01f, 0.01f);
		mSpecular = glm::vec3(0.4f, 0.4f, 0.4f);
		shininess = 0.078125f;
	}

	if (name == "cyan rubber")
	{
		mAmient = glm::vec3(0.0f, 0.05f, 0.05f);
		mDiffuse = glm::vec3(0.4f, 0.5f, 0.5f);
		mSpecular = glm::vec3(0.04f, 0.7f, 0.7f);
		shininess = 0.078125f;
	}

	if (name == "green rubber")
	{
		mAmient = glm::vec3(0.0f, 0.05f, 0.0f);
		mDiffuse = glm::vec3(0.4f, 0.5f, 0.4f);
		mSpecular = glm::vec3(0.04f, 0.7f, 0.04f);
		shininess = 0.078125f;
	}

	if (name == "red rubber")
	{
		mAmient = glm::vec3(0.05, 0.0f, 0.0f);
		mDiffuse = glm::vec3(0.5f, 0.4f, 0.4f);
		mSpecular = glm::vec3(0.7f, 0.04f, 0.04f);
		shininess = 0.078125f;
	}

	if (name == "white rubber")
	{
		mAmient = glm::vec3(0.05, 0.05f, 0.05f);
		mDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		mSpecular = glm::vec3(0.7f, 0.7f, 0.7f);
		shininess = 0.078125f;
	}

	if (name == "yellow rubber")
	{
		mAmient = glm::vec3(0.05, 0.05f, 0.0f);
		mDiffuse = glm::vec3(0.5f, 0.5f, 0.4f);
		mSpecular = glm::vec3(0.7f, 0.7f, 0.04f);
		shininess = 0.078125f;
	}

	newShader->setVec3("material.ambient", mAmient);
	newShader->setVec3("material.diffuse", mDiffuse);
	newShader->setVec3("material.specular", mSpecular);
	newShader->setFloat("material.shininess", shininess);
}

void Lighting::materialPropierties(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shiness) {
	newShader->setVec3("material.ambient", ambient);
	newShader->setVec3("material.diffuse", diffuse);
	newShader->setVec3("material.specular", specular);
	newShader->setFloat("material.shininess", shiness);
}

void Lighting::viewProyection(glm::mat4 view, glm::mat4 proy) {
	newShader->setMat4("projection", proy);
	newShader->setMat4("view", view);
}

void Lighting::modelLight(glm::mat4 model) {
	newShader->setMat4("model", model);
}




Lighting::~Lighting()
{
}

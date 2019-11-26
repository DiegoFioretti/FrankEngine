#ifndef RENDERER_H
#define RENDERER_H
#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"

class Renderer
{
private:
	Window* _window;
	unsigned int VertexArrayID;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 mvp;

	void UpdateMVP();
public:
	Renderer();
	~Renderer();

	bool Init(Window* window);
	void LoadIdentityMatrix();
	void SetModelMatrix(glm::mat4 mat);
	void MultiplyModelMatrix(glm::mat4 mat);
	void ClearScreen();
	void SetColor(float r, float g, float b, float a);
	bool Stop();
	glm::mat4& GetMVP() { return mvp; }

	void SwapBuffers();
};
#endif
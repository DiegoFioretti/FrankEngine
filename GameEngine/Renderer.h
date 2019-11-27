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
// Inicializador y final
	bool Init(Window* window);
	bool Stop();
// Matriz de modelo
	void LoadIdentityMatrix();
	void SetModelMatrix(glm::mat4 mat);
	void MultiplyModelMatrix(glm::mat4 mat);
// Generacion y destruccion de buffers
	unsigned int GenerateBuffer(float* buffer, int size);
	void DestroyBuffer(unsigned int buffer);
// Funciones de ventana
	void ClearScreen();
	void SetColor(float r, float g, float b, float a);
	void SwapBuffers();
// Model view projection
	glm::mat4& GetMVP() { return mvp; }
// Dibujado
	void BeginDraww(unsigned int attribID);
	void BindBuffer(unsigned int vertexBuffer, unsigned int attribID);
	void DrawBuffer(int size);
	void EndDraw(unsigned int attribID);
};
#endif
#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

bool Renderer::Init(Window* window) 
{
	_window = window;

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Creo vertex array
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);
	view = glm::lookAt(
		glm::vec3(0, 0, 3), // Camara esta en (4,3,3) en el espacio de mundo
		glm::vec3(0, 0, 0), // esta mira al origen
		glm::vec3(0, 1, 0)	// La cabeza esta por arriba (0,-1,0 para hacia mirar abajo)
	);

	model = glm::mat4(1.0f);

	UpdateMVP();

	return true;
}

void Renderer::UpdateMVP()
{
	mvp = projection * view * model;
}

void Renderer::SwapBuffers()
{
	glfwSwapBuffers((GLFWwindow*)_window);
}

void Renderer::ClearScreen() {
	glClear(GL_COLOR_BUFFER_BIT);
}
void Renderer::SetColor(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}

bool Renderer::Stop()
{
	if (VertexArrayID >= 0)
		glDeleteVertexArrays(1, &VertexArrayID);

	return true;
}
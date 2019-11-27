#include "Renderer.h"

Renderer::Renderer()
{
}
Renderer::~Renderer()
{
}

// Inicializador y final
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
bool Renderer::Stop()
{
	if (VertexArrayID >= 0)
		glDeleteVertexArrays(1, &VertexArrayID);

	return true;
}

// Matriz de modelo
void Renderer::LoadIdentityMatrix()
{

}
void Renderer::SetModelMatrix(glm::mat4 mat)
{

}
void Renderer::MultiplyModelMatrix(glm::mat4 mat)
{

}

// Generacion y destruccion de buffers
unsigned int Renderer::GenerateBuffer(float* buffer, int size)
{
	unsigned int vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);

	return vertexbuffer;
}
void Renderer::DestroyBuffer(unsigned int buffer)
{
	glDeleteBuffers(1, &buffer);
}

// Funciones de ventana
void Renderer::ClearScreen() {
	glClear(GL_COLOR_BUFFER_BIT);
}
void Renderer::SetColor(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}
void Renderer::SwapBuffers()
{
	glfwSwapBuffers((GLFWwindow*)_window);
}

// Model view projection
void Renderer::UpdateMVP()
{
	mvp = projection * view * model;
}

// Dibujado
void Renderer::BeginDraww(unsigned int attribID)
{
	glEnableVertexAttribArray(attribID);
}
void Renderer::BindBuffer(unsigned int vertexBuffer, unsigned int attribID) 
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(attribID,3,GL_FLOAT,GL_FALSE,0,(void*)0);
}
void Renderer::DrawBuffer(int size)
{
	glDrawArrays(GL_TRIANGLE_STRIP, 0, size);
}
void Renderer::EndDraw(unsigned int attribID)
{
	glDisableVertexAttribArray(attribID);
}
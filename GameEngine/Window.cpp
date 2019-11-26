#include "Window.h"

Window::Window()
{
	//This function initializes the GLFW library
	if (!glfwInit())
	{
		printf("GLFW no inicializado");
	}
	//Creacion de la ventana (ancho, alto, nombre , el monitor a usar en full screen o null en ventana, para compartir recursos de la ventana o null )
	_window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
	//Si la ventana no esta abierta cierra todo
	if (!_window)
	{
		//This function destroys all remaining windows and cursors, restores any modified gamma ramps and frees any other allocated resources
		glfwTerminate();
	}
	//Hace que haya un thread ocupado en la mantencion de la ventana
	glfwMakeContextCurrent(_window);
}

Window::Window(const char* name, int width, int height)
{
	//This function initializes the GLFW library
	if (!glfwInit())
	{
		printf("GLFW no inicializado");
	}
	//Creacion de la ventana (ancho, alto, nombre , el monitor a usar en full screen o null en ventana, para compartir recursos de la ventana o null )
	_window = glfwCreateWindow(width, height, name, NULL, NULL);
	//Si la ventana no esta abierta cierra todo
	if (!_window)
	{
		//This function destroys all remaining windows and cursors, restores any modified gamma ramps and frees any other allocated resources
		glfwTerminate();
	}
	//Hace que haya un thread ocupado en la mantencion de la ventana
	glfwMakeContextCurrent(_window);
}

bool Window::ShouldClose()
{
	if (_window)
	{
		return glfwWindowShouldClose(_window) != 0;
	}
	return true;
}

Window::~Window()
{
}

GLFWwindow* Window::window()
{
	return _window;
}

void Window::PollEvents() {
	glfwPollEvents();
}

bool Window::Stop()
{
	if (_window != NULL)
		glfwDestroyWindow(_window);

	_window = NULL;

	glfwTerminate();

	return true;
}
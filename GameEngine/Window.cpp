#include "Window.h"
#include <GLFW\glfw3.h>

bool firstMouse;
float lastX;
float lastY;
float xoffset;
float yoffset;
float sensitivity = 0.5f;
float yaw;
float pitch;

vec3 cameraDir;

void mouse_callback(GLFWwindow* win, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	xoffset = xpos - lastX;
	yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	cameraDir.x = cos(radians(yaw)) * cos(radians(pitch));
	cameraDir.y = sin(radians(pitch));
	cameraDir.z = sin(radians(yaw)) * cos(radians(pitch));
}

Window::Window()
{
	cameraPos.x = 0.0f;
	cameraPos.y = 0.0f;
	cameraPos.z = 10.0f;

	cameraDir.x = cos(radians(0.0f)) * cos(radians(0.0f));
	cameraDir.y = sin(radians(0.0f));
	cameraDir.z = sin(radians(0.0f)) * cos(radians(0.0f));

	cameraUp.x = 0.0f;
	cameraUp.y = 1.0f;
	cameraUp.z = 0.0f;
}

Window::~Window()
{
}
bool Window::Start(int width, int height, const char* name)
{
	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(width, height, name, NULL, NULL);

	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return false;
	}

	glfwSetInputMode((GLFWwindow*)window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	glfwSetCursorPosCallback((GLFWwindow*)window, mouse_callback);

	currentWdt = width;
	currentHgt = height;
	aspectRatio = sqrt((width * width) + (height * height));

	return true;
}

bool Window::Stop()
{
	if (window != NULL)
		glfwDestroyWindow((GLFWwindow*)window);
	window = NULL;
	glfwTerminate();
	return true;
}

bool Window::ShouldClose()
{
	if(window)
		return glfwWindowShouldClose((GLFWwindow*)window);
	
}

void Window::PollEvents()
{
	glfwPollEvents();
}

void* Window::GetWindow() {
	return window;
}

float Window::GetWndWidth() 
{
	return currentWdt;
}

float Window::GetWndHeight() 
{
	return currentHgt;
}

float Window::GetAspectRatio()
{
	return aspectRatio;
}

void Window::CameraMoveForward(float speed)
{
	cameraPos[0] += speed * cameraDir.x;
	cameraPos[1] += speed * cameraDir.y;
	cameraPos[2] += speed * cameraDir.z;
}

void Window::CameraTranslate(float x, float y, float z)
{
	cameraPos[0] += x;
	cameraPos[1] += y;
	cameraPos[2] += z;
}

void Window::CameraRotate(float pitch, float yaw)
{
	cameraDir.x = cos(radians(yaw)) * cos(radians(pitch));
	cameraDir.y = sin(radians(pitch));
	cameraDir.z = sin(radians(yaw)) * cos(radians(pitch));
}

vec3 Window:: GetCameraDir()
{
	return cameraDir;
}

vec3 Window::GetCameraPos()
{
	return cameraPos;
}

vec3 Window::GetCameraUp()
{
	return cameraUp;
}
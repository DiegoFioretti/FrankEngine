#ifndef WINDOW_H
#define WINDOW_H
#pragma once
#define WIDTH 640
#define HEIGHT 480

#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
private:
	GLFWwindow* _window;
public:
	Window();
	Window(const char* name, int width, int height);
	~Window();
	GLFWwindow* window();
	bool ShouldClose();
	const void* GetWindowPTR() { return (const void*)_window; }
	void PollEvents();
};
#endif
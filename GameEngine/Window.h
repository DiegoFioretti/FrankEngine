#pragma once
#include "Exports.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
class FRANKENGINE_API Window
{
private: 
	void * window;
public:
	Window();
	~Window();
	bool Start(int width, int height, const char* name);
	bool Stop();
	const void* GetWindowPtr() { return (const void*)window; }
	bool ShouldClose();
	void PollEvents();	
	void* GetWindow();
};


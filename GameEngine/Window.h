#pragma once
#include "Exports.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class FRANKENGINE_API Window
{
private: 
	void * window;
	int currentWdt;
	int currentHgt;
	float aspectRatio;
public:
	Window();
	~Window();
	bool Start(int width, int height, const char* name);
	bool Stop();
	const void* GetWindowPtr() { return (const void*)window; }
	bool ShouldClose();
	void PollEvents();	
	void* GetWindow();
	float GetWndWidth();
	float GetWndHeight();
	float GetAspectRatio();
};
#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

#pragma once
class Input
{
private:
	double timer = 0;
public:
	Input();
	~Input();
	bool keyCall(GLFWwindow* window, int key, int num);
	bool keyReleased[30];
	bool keyPress();
};

#endif INPUT_H
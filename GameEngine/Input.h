#pragma once
#include "Exports.h"
#include "Window.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class FRANKENGINE_API Input
{
private:
	Window *win;
	bool keyReleased[30];
public:
	Input(Window *window);
	bool keyCall(int key, int num);
};


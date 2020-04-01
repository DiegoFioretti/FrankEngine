#pragma once
#include "Exports.h"
#include "Window.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <iostream>
using namespace std;

class FRANKENGINE_API Input
{
private:
	Window *win;
	bool keyReleased[30];
public:
	Input(Window *window);
	bool keyCall(int key, int num);
};


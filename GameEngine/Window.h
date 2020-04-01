#pragma once
#include "Exports.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;

class FRANKENGINE_API Window
{
private: 
	void * window;
	int currentWdt;
	int currentHgt;
	float aspectRatio;
	//float yaw;			// Angulo de rotacion para Y
	//float pitch;		// Angulo de rotacion para X y Z
	vec3 cameraPos;
	vec3 cameraUp;
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
	void CameraMoveForward(float speed);
	void CameraTranslate(float x, float y, float z);
	void CameraRotate(float pitch, float yaw);
	vec3 GetCameraDir();
	vec3 GetCameraPos();
	vec3 GetCameraUp();
};
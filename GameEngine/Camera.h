#pragma once
#include "Exports.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

class FRANKENGINE_API Camera
{
private:
public:
	Camera(GLFWwindow* window);
	~Camera();
	void CameraMoveForward(float speed);
	void CameraTranslate(float x, float y, float z);
	void CameraRotate(float pitch, float yaw);
	vec3 GetCameraDir();
	vec3 GetCameraPos();
	vec3 GetCameraUp();
	void UpdateViewMatrix();
	mat4 GetViewMatrix();
};


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
	void CameraTranslateX(float x);
	void CameraTranslateY(float y);
	void CameraTranslateZ(float z);
	void CameraRotate(float pitch, float yaw);
	vec3 GetCameraDir();
	vec3 GetCameraPos();
	vec3 GetCameraUp();
	float FieldOfView();
	void UpdateViewMatrix();
	void UpdateProyectionMatrix();
	mat4 GetViewMatrix();
	mat4 GetProjectionMatrix();
};


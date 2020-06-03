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
	void CameraMoveLeft(float speed);
	void CameraTranslate(float x, float y, float z);
	void CameraTranslateX(float x);
	void CameraTranslateY(float y);
	void CameraTranslateZ(float z);
	void CameraRotate(float pitch, float yaw);
	void UpdateViewMatrix();
	void UpdateProyectionMatrix();
	vec3 GetCameraDir();
	float GetCameraYaw();
	float GetCameraPitch();
	vec3 GetCameraPos();
	vec3 GetCameraUp();
	mat4 GetViewMatrix();
	mat4 GetProjectionMatrix();
	void setCameraRot(float yaw, float pitch);
	void setCameraPos(float x, float y, float z);

};


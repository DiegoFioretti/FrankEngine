#include "Camera.h"
#include <string>
#include <iostream>



bool _firstMouse;
float _lastX;
float _lastY;
float _xoffset;
float _yoffset;
float _sensitivity = 0.5f;
float _yaw;
float _pitch;
float fov;
float _getAspectRatio;

vec3 _cameraPos;
vec3 _cameraDir;
vec3 _cameraUp;

mat4 _viewMatrix;
mat4 _projectionMatrix;

void mouse_callback(GLFWwindow* win, double xpos, double ypos)
{
	if (_firstMouse)
	{
		_lastX = xpos;
		_lastY = ypos;
		_firstMouse = false;
	}

	_xoffset = xpos - _lastX;
	_yoffset = _lastY - ypos;
	_lastX = xpos;
	_lastY = ypos;

	_xoffset *= _sensitivity;
	_yoffset *= _sensitivity;

	_yaw += _xoffset;
	_pitch += _yoffset;

	if (_pitch > 89.0f)
		_pitch = 89.0f;
	if (_pitch < -89.0f)
		_pitch = -89.0f;

	_cameraDir.x = cos(radians(_yaw)) * cos(radians(_pitch));
	_cameraDir.y = sin(radians(_pitch));
	_cameraDir.z = sin(radians(_yaw)) * cos(radians(_pitch));

	_viewMatrix = glm::lookAt(
		_cameraPos,
		_cameraPos + glm::normalize(_cameraDir),
		_cameraUp
	);
}

void scroll_callback(GLFWwindow* win, double xoffset, double yoffset)
{
	if (fov > 1.0f && fov < 90.0f)
		fov -= yoffset;
	else if (fov <= 1.0f)
		fov = 2.0f;
	else if (fov >= 90.0f)
		fov = 89.0f;
	
	_projectionMatrix = glm::perspective(glm::radians(fov), _getAspectRatio, 1.0f, 1000.0f);
}


float Camera::FieldOfView() {
	return fov;
}

Camera::Camera(GLFWwindow* window)
{
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);


	_firstMouse = true;
	_lastX = 0.0f;
	_lastY = 0.0f;
	_xoffset = 0.0f;
	_yoffset = 0.0f;
	_sensitivity = 0.5f;
	_yaw = 0.0f;
	_pitch = 0.0f;
	_getAspectRatio = 600.f / 800.f;
	fov = 45.f;

	_cameraPos = vec3(0.0f, 0.0f, 0.0f);
	_cameraDir = vec3(0.0f, 0.0f, 0.0f);
	_cameraUp = vec3(0.0f, 1.0f, 0.0f);

	_viewMatrix = glm::lookAt(
		_cameraPos,									// Position Vector
		_cameraPos + glm::normalize(_cameraDir),	// Direction Vector
		_cameraUp									// Up Vector
	);

	_projectionMatrix = glm::perspective(fov, _getAspectRatio, 1.0f, 100.0f);
	std::cout <<"Fov:" <<fov;
	std::cout << "_getAspectRatio:" << _getAspectRatio;
	
}

Camera::~Camera()
{
}



void Camera::UpdateViewMatrix()
{
	_viewMatrix = glm::lookAt(
		_cameraPos,
		_cameraPos + glm::normalize(_cameraDir),
		_cameraUp
	);
}

void Camera::CameraMoveForward(float speed)
{
	_cameraPos.x += speed * _cameraDir.x;
	_cameraPos.y += speed * _cameraDir.y;
	_cameraPos.z += speed * _cameraDir.z;

	UpdateViewMatrix();
}

void Camera::CameraMoveLeft(float speed)
{
	_cameraPos -= glm::normalize(glm::cross(_cameraDir, _cameraUp)) * speed;
	UpdateViewMatrix();
}

void Camera::CameraTranslate(float x, float y, float z)
{
	_cameraPos.x += x;
	_cameraPos.y += y;
	_cameraPos.z += z;

	UpdateViewMatrix();
}

void Camera::CameraTranslateX(float x)
{
	_cameraPos.x += x;

	UpdateViewMatrix();
}

void Camera::CameraTranslateY(float y)
{
	_cameraPos.y += y;

	UpdateViewMatrix();
}

void Camera::CameraTranslateZ( float z)
{

	_cameraPos.z += z;

	UpdateViewMatrix();
}

void Camera::CameraRotate(float pitch, float yaw)
{
	_cameraDir.x = cos(radians(yaw)) * cos(radians(pitch));
	_cameraDir.y = sin(radians(pitch));
	_cameraDir.z = sin(radians(yaw)) * cos(radians(pitch));

	UpdateViewMatrix();
}

vec3 Camera::GetCameraDir()
{
	return _cameraDir;
}

vec3 Camera::GetCameraPos()
{
	return _cameraPos;
}

vec3 Camera::GetCameraUp()
{
	return _cameraUp;
}

mat4 Camera::GetViewMatrix()
{
	return _viewMatrix;
}

mat4 Camera::GetProjectionMatrix() 
{
	return _projectionMatrix;
}
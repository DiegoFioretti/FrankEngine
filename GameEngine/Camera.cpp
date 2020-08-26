#include "Camera.h"
#include <string>
#include <iostream>



bool  _firstMouse;
float _lastX;
float _lastY;
float _xoffset;
float _yoffset;
float _sensitivity = 0.2f;
float _yaw;
float _pitch;
float fov;
float _getAspectRatio;

vec3 _cameraPos;
vec3 _cameraDir;
vec3 _cameraUp;

mat4 _viewMatrix;
mat4 _projectionMatrix;



//Da informacion del movimiento del mouse cada vez que se mueve
void mouse_callback(GLFWwindow* win, double xpos, double ypos)
{
	//Cuando inicia no tiene una ultima pos
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

	_yaw   += _xoffset;
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

void Camera::ProcessFrustrum() 
{
	projSource = (const float*) glm::value_ptr(_projectionMatrix);
	viewSource = (const float*)glm::value_ptr(_viewMatrix);
	for (size_t i = 0; i < 16; i++)
	{
		proj[i] = projSource[i];
		view[i] = viewSource[i];
	}

	/* Combine the two matrices (multiply projection by modelview) */
	clip[0] = view[0] * proj[0] + view[1] * proj[4] + view[2] * proj[8] + view[3] * proj[12];
	clip[1] = view[0] * proj[1] + view[1] * proj[5] + view[2] * proj[9] + view[3] * proj[13];
	clip[2] = view[0] * proj[2] + view[1] * proj[6] + view[2] * proj[10] + view[3] * proj[14];
	clip[3] = view[0] * proj[3] + view[1] * proj[7] + view[2] * proj[11] + view[3] * proj[15];

	clip[4] = view[4] * proj[0] + view[5] * proj[4] + view[6] * proj[8] + view[7] * proj[12];
	clip[5] = view[4] * proj[1] + view[5] * proj[5] + view[6] * proj[9] + view[7] * proj[13];
	clip[6] = view[4] * proj[2] + view[5] * proj[6] + view[6] * proj[10] + view[7] * proj[14];
	clip[7] = view[4] * proj[3] + view[5] * proj[7] + view[6] * proj[11] + view[7] * proj[15];

	clip[8] = view[8] * proj[0] + view[9] * proj[4] + view[10] * proj[8] + view[11] * proj[12];
	clip[9] = view[8] * proj[1] + view[9] * proj[5] + view[10] * proj[9] + view[11] * proj[13];
	clip[10] = view[8] * proj[2] + view[9] * proj[6] + view[10] * proj[10] + view[11] * proj[14];
	clip[11] = view[8] * proj[3] + view[9] * proj[7] + view[10] * proj[11] + view[11] * proj[15];

	clip[12] = view[12] * proj[0] + view[13] * proj[4] + view[14] * proj[8] + view[15] * proj[12];
	clip[13] = view[12] * proj[1] + view[13] * proj[5] + view[14] * proj[9] + view[15] * proj[13];
	clip[14] = view[12] * proj[2] + view[13] * proj[6] + view[14] * proj[10] + view[15] * proj[14];
	clip[15] = view[12] * proj[3] + view[13] * proj[7] + view[14] * proj[11] + view[15] * proj[15];

	/* Extract the numbers for the RIGHT plane */
	frustum[0][0] = clip[3] - clip[0];
	frustum[0][1] = clip[7] - clip[4];
	frustum[0][2] = clip[11] - clip[8];
	frustum[0][3] = clip[15] - clip[12];

	/* Normalize the result */
	t = sqrt(frustum[0][0] * frustum[0][0] + frustum[0][1] * frustum[0][1] + frustum[0][2] * frustum[0][2]);
	frustum[0][0] /= t;
	frustum[0][1] /= t;
	frustum[0][2] /= t;
	frustum[0][3] /= t;

	/* Extract the numbers for the LEFT plane */
	frustum[1][0] = clip[3] + clip[0];
	frustum[1][1] = clip[7] + clip[4];
	frustum[1][2] = clip[11] + clip[8];
	frustum[1][3] = clip[15] + clip[12];

	/* Normalize the result */
	t = sqrt(frustum[1][0] * frustum[1][0] + frustum[1][1] * frustum[1][1] + frustum[1][2] * frustum[1][2]);
	frustum[1][0] /= t;
	frustum[1][1] /= t;
	frustum[1][2] /= t;
	frustum[1][3] /= t;

	/* Extract the BOTTOM plane */
	frustum[2][0] = clip[3] + clip[1];
	frustum[2][1] = clip[7] + clip[5];
	frustum[2][2] = clip[11] + clip[9];
	frustum[2][3] = clip[15] + clip[13];

	/* Normalize the result */
	t = sqrt(frustum[2][0] * frustum[2][0] + frustum[2][1] * frustum[2][1] + frustum[2][2] * frustum[2][2]);
	frustum[2][0] /= t;
	frustum[2][1] /= t;
	frustum[2][2] /= t;
	frustum[2][3] /= t;

	/* Extract the TOP plane */
	frustum[3][0] = clip[3] - clip[1];
	frustum[3][1] = clip[7] - clip[5];
	frustum[3][2] = clip[11] - clip[9];
	frustum[3][3] = clip[15] - clip[13];

	/* Normalize the result */
	t = sqrt(frustum[3][0] * frustum[3][0] + frustum[3][1] * frustum[3][1] + frustum[3][2] * frustum[3][2]);
	frustum[3][0] /= t;
	frustum[3][1] /= t;
	frustum[3][2] /= t;
	frustum[3][3] /= t;

	/* Extract the FAR plane */
	frustum[4][0] = clip[3] - clip[2];
	frustum[4][1] = clip[7] - clip[6];
	frustum[4][2] = clip[11] - clip[10];
	frustum[4][3] = clip[15] - clip[14];

	/* Normalize the result */
	t = sqrt(frustum[4][0] * frustum[4][0] + frustum[4][1] * frustum[4][1] + frustum[4][2] * frustum[4][2]);
	frustum[4][0] /= t;
	frustum[4][1] /= t;
	frustum[4][2] /= t;
	frustum[4][3] /= t;

	/* Extract the NEAR plane */
	frustum[5][0] = clip[3] + clip[2];
	frustum[5][1] = clip[7] + clip[6];
	frustum[5][2] = clip[11] + clip[10];
	frustum[5][3] = clip[15] + clip[14];

	/* Normalize the result */
	t = sqrt(frustum[5][0] * frustum[5][0] + frustum[5][1] * frustum[5][1] + frustum[5][2] * frustum[5][2]);
	frustum[5][0] /= t;
	frustum[5][1] /= t;
	frustum[5][2] /= t;
	frustum[5][3] /= t;
}

//Da informacion del scroll de mouse cada vez que se mueve, se usa para hacer "Zoom"
void scroll_callback(GLFWwindow* win, double xoffset, double yoffset)
{
	if (fov > 1.0f && fov < 90.0f)
		fov -= yoffset;
	else if (fov <= 1.0f)
		fov = 2.0f;
	else if (fov >= 90.0f)
		fov = 89.0f;
	
	_projectionMatrix = glm::perspective(glm::radians(fov), _getAspectRatio, 1.0f, 1900.0f);
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
	_sensitivity = 0.2f;
	_yaw = 0.0f;
	_pitch = 0.0f;
	_getAspectRatio = 1024.f / 768.f;
	fov = 45.f;

	_cameraPos = vec3(0.0f, 0.0f, 0.0f);
	_cameraDir = vec3(0.00001f, 0.000001f, 0.000001f);
	_cameraUp = vec3(0.0f, 1.0f, 0.0f);

	_viewMatrix = glm::lookAt(
		_cameraPos,									// Position Vector
		_cameraPos + glm::normalize(_cameraDir),	// Direction Vector
		_cameraUp									// Up Vector
	);

	_projectionMatrix = glm::perspective(fov, _getAspectRatio, 1.0f, 1900.0f);
	std::cout << "Fov:" << fov;
	std::cout << "_getAspectRatio:" << _getAspectRatio;

	ProcessFrustrum();
}


Camera::~Camera()
{
	delete projSource;
	delete viewSource;
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

void Camera::CameraRotate(float pitch, float yaw){
	_cameraDir.x = cos(radians(yaw)) * cos(radians(pitch));
	_cameraDir.y = sin(radians(pitch));
	_cameraDir.z = sin(radians(yaw)) * cos(radians(pitch));

	UpdateViewMatrix();
}

vec3 Camera::GetCameraDir()
{
	return _cameraDir;
}

float Camera::GetCameraYaw() {
	return _yaw;
}

float Camera::GetCameraPitch() {
	return _pitch;
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

void Camera::setCameraRot(float yaw, float pitch){
	_yaw = yaw;
	_pitch = pitch;
	_cameraDir.x = cos(radians(_yaw)) * cos(radians(_pitch));
	_cameraDir.y = sin(radians(_pitch));
	_cameraDir.z = sin(radians(_yaw)) * cos(radians(_pitch));

	UpdateViewMatrix();
}

void Camera::setCameraPos(float x, float y, float z) {
	_cameraPos.x = x;
	_cameraPos.y = y;
	_cameraPos.z = z;

	UpdateViewMatrix();
}
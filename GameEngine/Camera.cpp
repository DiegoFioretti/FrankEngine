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

float nearDist; // Distancia de plano cercano
float Hnear; // Altura del plano cercano
float Wnear; // Ancho del plano cercano
float farDist; // Distancia de plano lejano
float Hfar; // Altura del plano lejano
float Wfar; // Ancho del plano lejano

vec3 ntl, // Punto cercano|top|izquierda
	 ntr, // Punto cercano|top|derecha
	 nbl, // Punto cercano|bottom|izquierda
	 nbr, // Punto cercano|bottom|derecha
	 ftl, // Punto lejano|top|izquierda
	 ftr, // Punto lejano|top|derecha
	 fbl, // Punto lejano|bottom|izquierda
	 fbr; // Punto lejano|bottom|derecha

vec3 _cameraPos;
vec3 _cameraDir;
vec3 _cameraUp;

mat4 _viewMatrix;
mat4 _projectionMatrix;

void updatePlanes() 
{
	// Plano cercano
	Hnear = 2 * tan(fov / 2) * nearDist;
	Wnear = Hnear * _getAspectRatio;
	// Plano lejano
	Hfar = 2 * tan(fov / 2) * farDist;
	Wfar = Hfar * _getAspectRatio;
}

void Camera::MeasurePlanes(int plane,vec3 v1, vec3 v2, vec3 v3)
{
	vec3 aux1, aux2;

	aux1 = v1 - v2;
	aux2 = v3 - v2;

	frustum[plane].normal = aux2 * aux1;

	glm::normalize(frustum[plane].normal);
	frustum[plane].point = v2;
	frustum[plane].d = -(frustum[plane].normal.x * frustum[plane].point.x + frustum[plane].normal.y * frustum[plane].point.y + frustum[plane].normal.z * frustum[plane].point.z);
}

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

	updatePlanes();

}

void Camera::ProcessFrustrum()
{
	vec3 frontCenter = _cameraPos + _cameraDir * nearDist;
	vec3 backCenter = _cameraPos + _cameraDir * farDist;

	vec3 leftPlaneVec = (frontCenter - (vec3)right * nearWidht) - _cameraPos;
	vec3 rightPlaneVec = (frontCenter + (vec3)right * nearWidht) - _cameraPos;
	vec3 topPlaneVec = (frontCenter + _cameraUp * nearHeight) - _cameraPos;
	vec3 bottomPlaneVec = (frontCenter - _cameraUp * nearHeight) - _cameraPos;

	vec3 normalLeft = normalize(cross(leftPlaneVec, _cameraUp));
	vec3 normalRight = -normalize(cross(rightPlaneVec, _cameraUp));
	vec3 normalTop = normalize(cross(topPlaneVec, right));
	vec3 normalBottom = -normalize(cross(bottomPlaneVec, right));

	frustumPlanes[NEAR] = GeneratePlane(-_cameraDir, frontCenter);
	frustumPlanes[FAR] = GeneratePlane(_cameraDir, backCenter);
	frustumPlanes[LEFT] = GeneratePlane(normalLeft, _cameraPos);
	frustumPlanes[RIGHT] = GeneratePlane(normalRight, _cameraPos);
	frustumPlanes[TOP] = GeneratePlane(normalTop, _cameraPos);
	frustumPlanes[BOTTOM] = GeneratePlane(normalBottom, _cameraPos);


	/*
	updatePlanes();

	vec3 nc, fc, X, Y, Z;

	// compute the Z axis of camera
	// this axis points in the opposite direction from 
	// the looking direction
	Z = _cameraPos - _cameraDir;
	glm::normalize(Z);

	// X axis of camera with given "up" vector and Z axis
	X = _cameraUp * Z;
	glm::normalize(X);

	// the real "up" vector is the cross product of Z and X
	Y = Z * X;

	// compute the centers of the near and far planes
	nc = _cameraPos - Z * nearDist;
	fc = _cameraPos - Z * farDist;

	// compute the 4 corners of the frustum on the near plane
	ntl = nc + Y * Hnear - X * Wnear;
	ntr = nc + Y * Hnear + X * Wnear;
	nbl = nc - Y * Hnear - X * Wnear;
	nbr = nc - Y * Hnear + X * Wnear;

	// compute the 4 corners of the frustum on the far plane
	ftl = fc + Y * Hfar - X * Wfar;
	ftr = fc + Y * Hfar + X * Wfar;
	fbl = fc - Y * Hfar - X * Wfar;
	fbr = fc - Y * Hfar + X * Wfar;

	// compute the six planes
	// the function set3Points assumes that the points
	// are given in counter clockwise order
	// TOP PANEL
	MeasurePlanes(0, ntr, ntl, ftl);
	//BOTTOM PANEL
	MeasurePlanes(1, nbl, nbr, fbr);
	// LEFT PANEL
	MeasurePlanes(2, ntl, nbl, fbl);
	// RIGHT PANEL
	MeasurePlanes(3, nbr, ntr, fbr);
	// NEAR PANEL
	MeasurePlanes(4, ntl, ntr, nbr);
	// FAR PANEL
	MeasurePlanes(5, ftr, ftl, fbl);*/
}

vec4 Camera::GeneratePlane(vec3 _normal, vec3 _point) {
	vec4 plane;

	plane.x = _normal.x;
	plane.y = _normal.y;
	plane.z = _normal.z;
	plane.w = -dot(_normal, _point);

	return plane;
}

bool Camera::FrustumCheck(vec3 boundingBox)
{

	bool isInsideFrustum = true;
	bool allOutsideFrustum = false;
	float distance;
	for (int i = 0; i < (int)FrustumPlanesEnums::CANT; i++)
	{
		allOutsideFrustum = false;
			distance = dot(vec3(frustumPlanes[i]), boundingBox + frustumPlanes[i].w);
			if (distance < 0.0f)
				break;
		
		if (allOutsideFrustum)
		{
			isInsideFrustum = false;
			break;
		}
	}
	return isInsideFrustum;
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
	
	_projectionMatrix = glm::perspective(glm::radians(fov), _getAspectRatio, nearDist, farDist);

	updatePlanes();
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
	aspectRatioWidth = 16.0f;
	aspectRatioHeight = 9.0f;
	fov = 45.f;
	tang = tan(radians(fov) * 0.5f);
	right = vec3(1.0f, 0.0f, 0.0f);
	nearDist = 1.0f;
	farDist = 1050.0f;
	nearHeight = nearDist * tang;
	nearWidht = nearHeight * (aspectRatioWidth / aspectRatioHeight);


	_cameraPos = vec3(0.0f, 0.0f, 0.0f);
	_cameraDir = vec3(0.f, 0.f, 1.f);
	_cameraUp = vec3(0.0f, 1.0f, 0.0f);

	_viewMatrix = glm::lookAt(
		_cameraPos,									// Position Vector
		_cameraPos + glm::normalize(_cameraDir),	// Direction Vector
		_cameraUp									// Up Vector
	);

	_projectionMatrix = glm::perspective(glm::radians(fov), _getAspectRatio, nearDist, farDist);
	std::cout << "Fov: " << fov;
	std::cout << " | _getAspectRatio: " << _getAspectRatio << std::endl;
	
	for (size_t i = 0; i < PCANT; i++)
	{
		frustum[i].normal.x = 0.0f;
		frustum[i].normal.y = 0.0f;
		frustum[i].normal.z = 0.0f;
		frustum[i].point.x = 0.0f;
		frustum[i].point.y = 0.0f;
		frustum[i].point.z = 0.0f;
		frustum[i].d = 0.0f;
	}

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

	ProcessFrustrum();
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
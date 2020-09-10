#pragma once
#include "Exports.h"
//#include "Transform.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#define PCANT 6

struct PlanePoints
{
	vec3 normal;
	vec3 point;
	float d;
};

enum FrustumPlanesEnums
{
	NEAR,
	FAR,
	LEFT,
	TOP,
	RIGHT,
	BOTTOM,
	CANT = 6
};

class FRANKENGINE_API Camera//: public Transform
{
private:
	const float* projSource;
	const float* viewSource;
	float tang;
	float nearHeight;
	float nearWidht;
	float aspectRatioWidth;
	float aspectRatioHeight;
	vec4 frustumPlanes[CANT];
	glm::vec3 right;

	void MeasurePlanes(int plane, vec3 v1, vec3 v2, vec3 v3);
public:
	PlanePoints frustum[PCANT];
	Camera(GLFWwindow* window);
	~Camera();
	void ProcessFrustrum();
	void CameraMoveForward(float speed);
	void CameraMoveLeft(float speed);
	void CameraTranslate(float x, float y, float z);
	void CameraTranslateX(float x);
	void CameraTranslateY(float y);
	void CameraTranslateZ(float z);
	void CameraRotate(float pitch, float yaw);
	void UpdateViewMatrix();
	vec3 GetCameraDir();
	float GetCameraYaw();
	float GetCameraPitch();
	vec3 GetCameraPos();
	vec3 GetCameraUp();
	mat4 GetViewMatrix();
	mat4 GetProjectionMatrix();
	void setCameraRot(float yaw, float pitch);
	void setCameraPos(float x, float y, float z);
	vec4 GeneratePlane(vec3 _normal, vec3 _point);
	bool FrustumCheck(vec3 boundingBox);

};


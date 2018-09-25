#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Object3D.h"

class Camera : public Object3D
{
public:
	glm::mat4 projection;
	double aspect;
	double near, far, fov;

	Camera(double _fov = 60.0, double _near = 0.1, double _far = 1000.0);

	void virtual updateMatrix();

	void updateProjectionMatrix(float width, float height);
};

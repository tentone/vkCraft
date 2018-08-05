#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include "Object3D.cpp"
#include "Geometry.cpp"

class Mesh : public Object3D
{
public:
	Geometry *geometry;

	Mesh(Geometry *_geometry)
	{
		geometry = _geometry;
	}
};

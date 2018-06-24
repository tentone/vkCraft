#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

class UniformBufferObject
{
public:
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};

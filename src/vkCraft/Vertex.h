#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <array>

/**
 * Vertex is used to represent vertex for geometries.
 *
 * A vertex is composed of a point, normal vector and texture uv.
 */
class Vertex
{
public:
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 uv;

	/**
	 * Get binding description for the vertex.
	 */
	static VkVertexInputBindingDescription getBindingDescription();

	/**
	 * Get attrubute description to pass information to the shader using correct location.
	 */
	static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();
};

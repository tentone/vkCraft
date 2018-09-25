#pragma once

#include <vector>

#include "Vertex.h"
#include "Device.h"
#include "BufferUtils.cpp"

/**
 * Stores geometry data and correspondent buffers.
 */
class Geometry
{
public:
	//Vertex
	std::vector<Vertex> vertices;
	VkBuffer vertexBuffer = VK_NULL_HANDLE;
	VkDeviceMemory vertexBufferMemory = VK_NULL_HANDLE;

	//Indices
	std::vector<uint32_t> indices;
	VkBuffer indexBuffer = VK_NULL_HANDLE;
	VkDeviceMemory indexBufferMemory = VK_NULL_HANDLE;

	/**
	 * Method to generate the geometry index and vertex data.
	 */
	virtual void generate();

	/**
	 * Check if geometry is ready to be drawn by the renderer.
	 */
	bool hasBuffers();

	/**
	 * Apply a matrix transformation to the geometry vertex position.
	 */
	void applyTransformationMatrix(glm::mat4 *matrix);

	/**
	 * Append another geometry data to this geometry.
	 */
	void merge(Geometry *geometry);

	/**
	 * Dispose the geometry.
	 */
	void dispose(VkDevice &device);
};
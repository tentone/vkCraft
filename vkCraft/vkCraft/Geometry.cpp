#pragma once

#include <vector>

#include "Vertex.cpp"
#include "Device.cpp"
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
	virtual void generate()
	{
		vertices = {};
		indices = {};
	}

	/**
	 * Check if geometry is ready to be drawn by the renderer.
	 */
	bool isReady()
	{
		return vertexBuffer != VK_NULL_HANDLE && indexBuffer != VK_NULL_HANDLE;
	}

	/**
	 * Apply a matrix transformation to the geometry vertex position.
	 */
	void applyTransformationMatrix(glm::mat4 matrix)
	{
		for (int i = 0; i < vertices.size(); i++)
		{
			glm::vec4 result = matrix * glm::vec4(vertices[i].pos, 1.0f);
			
			vertices[i].pos.x = result.x;
			vertices[i].pos.y = result.y;
			vertices[i].pos.z = result.z;
		}
	}

	/**
	 * Append another geometry data to this geometry.
	 */
	void merge(Geometry *geometry)
	{
		int initialSize = vertices.size();

		for (int i = 0; i < geometry->vertices.size(); i++)
		{
			vertices.push_back(geometry->vertices[i]);
		}

		for (int i = 0; i < geometry->indices.size(); i++)
		{
			indices.push_back(geometry->indices[i] + initialSize);
		}
	}

	/**
	 * Dispose the geometry.
	 */
	void dispose(VkDevice device)
	{
		vkDestroyBuffer(device, vertexBuffer, nullptr);
		vkFreeMemory(device, vertexBufferMemory, nullptr);

		vkDestroyBuffer(device, indexBuffer, nullptr);
		vkFreeMemory(device, indexBufferMemory, nullptr);
	}
};
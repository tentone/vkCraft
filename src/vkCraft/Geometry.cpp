#pragma once

#include "Geometry.h"

void Geometry::generate(){}

bool Geometry::hasBuffers()
{
	return vertexBuffer != VK_NULL_HANDLE && indexBuffer != VK_NULL_HANDLE;
}

void Geometry::applyTransformationMatrix(glm::mat4 *matrix)
{
	for (int i = 0; i < vertices.size(); i++)
	{
		glm::vec4 result = *matrix * glm::vec4(vertices[i].pos, 1.0f);
			
		vertices[i].pos.x = result.x;
		vertices[i].pos.y = result.y;
		vertices[i].pos.z = result.z;
	}
}

void Geometry::merge(Geometry *geometry)
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

void Geometry::dispose(VkDevice &device)
{
	vkDestroyBuffer(device, vertexBuffer, nullptr);
	vkFreeMemory(device, vertexBufferMemory, nullptr);

	vkDestroyBuffer(device, indexBuffer, nullptr);
	vkFreeMemory(device, indexBufferMemory, nullptr);
}

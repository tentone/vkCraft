#pragma once

#include <vector>
#include "Vertex.cpp"

class Geometry
{
public:
	//Geometry mode (vertex or indexed)


	//Vertex
	std::vector<Vertex> vertices;
	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;

	//Indices
	std::vector<uint32_t> indices;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;

	//Method to generate the geometry index and vertex data
	virtual void generate(){}

	//Create 
	void createBuffers(VkDevice device)
	{
		//TODO
	}

	void dispose(VkDevice device)
	{
		vkDestroyBuffer(device, vertexBuffer, nullptr);
		vkFreeMemory(device, vertexBufferMemory, nullptr);

		vkDestroyBuffer(device, indexBuffer, nullptr);
		vkFreeMemory(device, indexBufferMemory, nullptr);
	}
};
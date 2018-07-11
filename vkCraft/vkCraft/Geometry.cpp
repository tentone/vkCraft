#pragma once

#include <vector>
#include "Vertex.cpp"

class Geometry
{
public:
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

	//Create the vertex and index buffers
	void createBuffers(VkDevice device)
	{
		//TODO <ADD CODE HERE>
	}
	
	//Dispose the geometry
	void dispose(VkDevice device)
	{
		vkDestroyBuffer(device, vertexBuffer, nullptr);
		vkFreeMemory(device, vertexBufferMemory, nullptr);

		vkDestroyBuffer(device, indexBuffer, nullptr);
		vkFreeMemory(device, indexBufferMemory, nullptr);
	}
};
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
	
	//Apply a matrix transformation to the geometry vertex position
	void applyTransformationMatrix(glm::mat4 matrix)
	{
		//TODO <ADD CODE HERE>
	}

	//Append another geometry data to this geometry
	void append(Geometry *geometry)
	{
		//TODO <ADD CODE HERE>
	}

	//Dispose the geometry
	virtual void dispose(VkDevice device)
	{
		vkDestroyBuffer(device, vertexBuffer, nullptr);
		vkFreeMemory(device, vertexBufferMemory, nullptr);

		vkDestroyBuffer(device, indexBuffer, nullptr);
		vkFreeMemory(device, indexBufferMemory, nullptr);
	}
};
#pragma once

#include <vector>

#include "Vertex.cpp"
#include "Device.cpp"
#include "BufferUtils.cpp"

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
	virtual void generate()
	{
		vertices = {};
		indices = {};
	}

	//Create the vertex and index buffers
	void createBuffers(Device *device)
	{
		//createVertexBuffer(*device);
		//createIndexBuffer(*device);
	}

	/*
	//Create vertex buffer
	void createVertexBuffer(Device device)
	{
		VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		BufferUtils::createBuffer(device, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(device.logical, stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, vertices.data(), (size_t)bufferSize);
		vkUnmapMemory(device.logical, stagingBufferMemory);

		BufferUtils::createBuffer(device, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, geometry->vertexBuffer, geometry->vertexBufferMemory);

		//Copy from CPU memory buffer to GPU memory buffer
		copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

		//Clean the stagging (CPU) buffer
		vkDestroyBuffer(device.logical, stagingBuffer, nullptr);
		vkFreeMemory(device.logical, stagingBufferMemory, nullptr);
	}

	//Create index buffer
	void createIndexBuffer(Device device)
	{
		VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		BufferUtils::createBuffer(device, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(device.logical, stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, indices.data(), (size_t)bufferSize);
		vkUnmapMemory(device.logical, stagingBufferMemory);

		BufferUtils::createBuffer(device, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, geometry->indexBuffer, geometry->indexBufferMemory);

		copyBuffer(stagingBuffer, indexBuffer, bufferSize);

		vkDestroyBuffer(device.logical, stagingBuffer, nullptr);
		vkFreeMemory(device.logical, stagingBufferMemory, nullptr);
	}
	*/

	//Apply a matrix transformation to the geometry vertex position
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

	//Append another geometry data to this geometry
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

	//Dispose the geometry
	void dispose(VkDevice device)
	{
		vkDestroyBuffer(device, vertexBuffer, nullptr);
		vkFreeMemory(device, vertexBufferMemory, nullptr);

		vkDestroyBuffer(device, indexBuffer, nullptr);
		vkFreeMemory(device, indexBufferMemory, nullptr);
	}
};
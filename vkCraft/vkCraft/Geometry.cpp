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
	VkBuffer vertexBuffer = VK_NULL_HANDLE;
	VkDeviceMemory vertexBufferMemory = VK_NULL_HANDLE;

	//Indices
	VkBuffer indexBuffer = VK_NULL_HANDLE;
	VkDeviceMemory indexBufferMemory = VK_NULL_HANDLE;

	/**
	 * Method to generate the geometry index and vertex data.
	 */
	virtual void generate(Device *device, VkQueue *graphicsQueue, VkCommandPool *commandPool){}

	/**
	 * Check if geometry is ready to be drawn by the renderer.
	 */
	bool hasBuffers()
	{
		return vertexBuffer != VK_NULL_HANDLE && indexBuffer != VK_NULL_HANDLE;
	}

	/**
	 * Create buffers for this geometry.
	 */
	void createGeometryBuffers(Device *device, VkQueue *graphicsQueue, VkCommandPool *commandPool, std::vector<uint32_t> *indices, std::vector<Vertex> *vertices)
	{
		if (this->hasBuffers() || indices->size() == 0 || vertices->size() == 0)
		{
			return;
		}

		VkDeviceSize vertexBufferSize = sizeof(Vertex) * vertices->size();
		VkDeviceSize indexBufferSize = sizeof(uint32_t) * indices->size();

		VkBuffer indexStagingBuffer, vertexStagingBuffer;
		VkDeviceMemory indexStagingBufferMemory, vertexStagingBufferMemory;

		//Create CPU buffers
		BufferUtils::createBuffer(*device, vertexBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, vertexStagingBuffer, vertexStagingBufferMemory);
		BufferUtils::createBuffer(*device, indexBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, indexStagingBuffer, indexStagingBufferMemory);

		//Map memory
		void *vertexData, *indexData;
		vkMapMemory(device->logical, vertexStagingBufferMemory, 0, vertexBufferSize, 0, &vertexData);
		vkMapMemory(device->logical, indexStagingBufferMemory, 0, indexBufferSize, 0, &indexData);

		memcpy(vertexData, vertices->data(), (size_t)vertexBufferSize);
		memcpy(indexData, indices->data(), (size_t)indexBufferSize);

		vkUnmapMemory(device->logical, vertexStagingBufferMemory);
		vkUnmapMemory(device->logical, indexStagingBufferMemory);

		//Create GPU buffers
		BufferUtils::createBuffer(*device, vertexBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);
		BufferUtils::createBuffer(*device, indexBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

		//Copy from CPU buffer to GPU buffer
		BufferUtils::copyBuffer(device, graphicsQueue, commandPool, vertexStagingBuffer, vertexBuffer, vertexBufferSize);
		BufferUtils::copyBuffer(device, graphicsQueue, commandPool, indexStagingBuffer, indexBuffer, indexBufferSize);

		//Clean the stagging (CPU) buffer
		vkDestroyBuffer(device->logical, vertexStagingBuffer, nullptr);
		vkFreeMemory(device->logical, vertexStagingBufferMemory, nullptr);
		vkDestroyBuffer(device->logical, indexStagingBuffer, nullptr);
		vkFreeMemory(device->logical, indexStagingBufferMemory, nullptr);
	}

	/**
	 * Apply a matrix transformation to the geometry vertex position.
	 */
	void applyTransformationMatrix(glm::mat4 *matrix)
	{
		/*
		for (int i = 0; i < vertices.size(); i++)
		{
			glm::vec4 result = *matrix * glm::vec4(vertices[i].pos, 1.0f);
			
			vertices[i].pos.x = result.x;
			vertices[i].pos.y = result.y;
			vertices[i].pos.z = result.z;
		}
		*/
	}

	/**
	 * Append another geometry data to this geometry.
	 */
	void merge(Geometry *geometry)
	{
		/*
		int initialSize = vertices.size();

		for (int i = 0; i < geometry->vertices.size(); i++)
		{
			vertices.push_back(geometry->vertices[i]);
		}

		for (int i = 0; i < geometry->indices.size(); i++)
		{
			indices.push_back(geometry->indices[i] + initialSize);
		}
		*/
	}

	/**
	 * Dispose the geometry.
	 */
	void dispose(VkDevice &device)
	{
		vkDestroyBuffer(device, vertexBuffer, nullptr);
		vkFreeMemory(device, vertexBufferMemory, nullptr);

		vkDestroyBuffer(device, indexBuffer, nullptr);
		vkFreeMemory(device, indexBufferMemory, nullptr);
	}
};
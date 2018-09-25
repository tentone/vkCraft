#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>

#include "Device.h"
#include "CommandBufferUtils.h"

class BufferUtils
{
public:
	//Generic buffer creation
	static void createBuffer(Device device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

	//Copy the contents of a buffer to another buffer (move to BufferUtils)
	static void copyBuffer(Device *device, VkQueue *graphicsQueue, VkCommandPool *commandPool, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
};
#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Device.h"

class CommandBufferUtils
{
public:
	//Begin a single time use command buffer
	static VkCommandBuffer beginSingleTimeCommands(Device *device, VkCommandPool *commandPool);

	//End single time command buffer
	static void endSingleTimeCommands(Device *device, VkQueue *graphicsQueue, VkCommandPool *commandPool, VkCommandBuffer *commandBuffer);
};
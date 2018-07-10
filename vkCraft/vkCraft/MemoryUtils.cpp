#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class MemoryUtils
{
public:
	//Find proper memory type for data defined by properties
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
	{
		/*
		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
		{
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
		{
		return i;
		}
		}

		throw std::runtime_error("vkCraft: Failed to find suitable memory type!");
		*/
	}
};
#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>
#include <iostream>

#include "QueueFamilyIndices.h"

/**
 * The device class handles everything related with logical and physical device configuration.
 */
class Device
{
public:
	/**
	 * The physical device is mostly used to check for the GPU hardware capabilities.
	 */
	VkPhysicalDevice physical = VK_NULL_HANDLE;

	/**
	 * The logical device is used to execute all the vulkan operations.
	 */
	VkDevice logical = VK_NULL_HANDLE;

	Device();

	Device(VkPhysicalDevice _physical);

	Device(VkPhysicalDevice _physical, VkDevice _logical);

	/**
	 * Dispose device and all the buffers, pools associated with it.
	 */
	void dispose();

	/**
	 * Check which queue families are supported by the physical device.
	 *
	 * We only need it to support graphics rendering to a surface.
	 */
	QueueFamilyIndices getQueueFamilyIndices(VkSurfaceKHR surface);

	/**
	 * Find a proper memory type for data defined by the memory properties specified.
	 */
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
};

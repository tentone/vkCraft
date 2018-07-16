#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>
#include <iostream>

#include "QueueFamilyIndices.cpp"

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

	Device(){}

	Device(VkPhysicalDevice _physical)
	{
		physical = _physical;
	}
	
	Device(VkPhysicalDevice _physical, VkDevice _logical)
	{
		physical = _physical;
		logical = _logical;
	}

	/**
	 * Dispose device and all the buffers, pools associated with it.
	 */
	void dispose()
	{
		vkDestroyDevice(logical, nullptr);
	}

	/**
	 * Check which queue families are supported by the physical device.
	 *
	 * We only need it to support graphics rendering to a surface.
	 */
	QueueFamilyIndices getQueueFamilyIndices(VkSurfaceKHR surface)
	{
		QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(physical, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(physical, &queueFamilyCount, queueFamilies.data());

		int i = 0;
		for (const auto& queueFamily : queueFamilies)
		{
			if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				indices.graphicsFamily = i;
			}

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(physical, i, surface, &presentSupport);

			if (queueFamily.queueCount > 0 && presentSupport)
			{
				indices.presentFamily = i;
			}

			if (indices.isComplete())
			{
				break;
			}

			i++;
		}

		return indices;
	}

	/**
	 * Find a proper memory type for data defined by the memory properties specified.
	 */
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
	{
		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(physical, &memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
		{
			if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
			{
				return i;
			}
		}

		throw std::runtime_error("vkCraft: Failed to find suitable memory type!");
	}
};

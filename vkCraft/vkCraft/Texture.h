#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>

class Texture
{
public:
	VkImage image;
	VkDeviceMemory imageMemory;
	VkImageView imageView;

	/**
	 * Magnification iltering configuration.
	 */
	VkFilter magFilter = VK_FILTER_NEAREST; //VK_FILTER_LINEAR | VK_FILTER_NEAREST

	/**
	 * Minification filtering configuration.
	 */
	VkFilter minFilter = VK_FILTER_NEAREST;

	/**
	 * Create a texture sampler, used for texture access in shaders.
	 */
	void createSampler(VkDevice &device, VkSampler &textureSampler);

	/**
	 * Dispose texture from memory.
	 */
	void dispose(VkDevice *device);
};
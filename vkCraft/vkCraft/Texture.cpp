#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class Texture
{
public:
	VkImage image;
	VkDeviceMemory memory;
	VkImageView vieww;
};
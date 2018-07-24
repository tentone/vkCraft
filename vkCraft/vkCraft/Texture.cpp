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

	//Create a texture sampler, used for texture access in shaders.
	void createSampler(VkDevice *device, VkSampler *textureSampler)
	{
		VkSamplerCreateInfo samplerInfo = {};
		samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		samplerInfo.magFilter = VK_FILTER_LINEAR;
		samplerInfo.minFilter = VK_FILTER_LINEAR;
		samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		samplerInfo.anisotropyEnable = VK_TRUE;
		samplerInfo.maxAnisotropy = 16;
		samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
		samplerInfo.unnormalizedCoordinates = VK_FALSE;
		samplerInfo.compareEnable = VK_FALSE;
		samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
		samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

		if (vkCreateSampler(*device, &samplerInfo, nullptr, textureSampler) != VK_SUCCESS)
		{
			throw std::runtime_error("vkCraft: Failed to create texture sampler!");
		}
	}

	//Dispose texture
	void dispose(VkDevice *device)
	{
		vkDestroyImageView(*device, imageView, nullptr);
		vkDestroyImage(*device, image, nullptr);
		vkFreeMemory(*device, imageMemory, nullptr);
	}
};
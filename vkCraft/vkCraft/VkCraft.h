#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <array>
#include <set>
#include <ctime>

#include "Device.h"
#include "BufferUtils.h"
#include "QueueFamilyIndices.h"
#include "SwapChainSupportDetails.h"
#include "UniformBufferObject.h"
#include "Texture.h"
#include "FileUtils.h"
#include "CommandBufferUtils.h"
#include "Object3D.h"
#include "FirstPersonCamera.h"
#include "ChunkWorld.h"

class VkCraft
{
public:
	//Maximum amount of frames that can be renderer simultaneously
	const int CONCURRENT_FRAMES = 1;

	//Validation layer control
	const bool ENABLE_VALIDATION_LAYERS = true;

	//Vulkan context and window
	GLFWwindow *window;
	VkInstance instance;
	VkSurfaceKHR surface;

	//Error handler
	VkDebugReportCallbackEXT callback;

	Device device;

	//GRAPHICS QUEUE CLASS
	VkQueue graphicsQueue;
	VkQueue presentQueue;

	//SWAP CHAIN HANDLER CLASS
	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	std::vector<VkImageView> swapChainImageViews;
	std::vector<VkFramebuffer> swapChainFramebuffers;

	VkRenderPass renderPass;

	VkPipelineLayout pipelineLayout;
	VkDescriptorSetLayout descriptorSetLayout;
	VkPipeline graphicsPipeline;

	VkCommandPool commandPool;

	//Render pipeline
	VkCommandPool renderCommandPool;
	std::vector<VkCommandBuffer> renderCommandBuffers;

	//Uniform buffer
	VkBuffer uniformBuffer;
	VkDeviceMemory uniformBufferMemory;

	Texture texture;
	VkSampler textureSampler = VK_NULL_HANDLE;

	//Depth buffer
	Texture depth;

	//Descriptors
	VkDescriptorPool descriptorPool;
	VkDescriptorSet descriptorSet;

	//Syncronization semaphores (one for each concurrent frame)
	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	size_t currentFrame = 0;

	//Object3D and camera
	Object3D model;
	FirstPersonCamera camera;
	glm::ivec3 cameraIndex = { 1, 2, 3 };
	UniformBufferObject uniformBuf;
	double time, delta;

	ChunkWorld world = ChunkWorld(349995);

	/** 
	 * Use lugarG validation layers provided by the SDK.
	 */
	const std::vector<const char*> validationLayers =
	{
		"VK_LAYER_KHRONOS_validation"
	};

	const std::vector<const char*> deviceExtensions =
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	/**
	 * Declare the debug report extension
	 */
	VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);

	/**
	 *Destroy the debug report extension
	 */
	void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator);

	/**
	 * Start the application.
	 */
	void run();

	/**
	 * Logic loop where the draw call is made.
	 */
	void loop();

	/**
	 * Update the uniform buffers (and run some logic), before drawing the next frame.
	 */
	void update();

	/**
	 * Draw frame to the swap chain and display it.
	 */
	void render();

	/**
	 * Initialize the data structures, get devices and prepare vulkan for rendering.
	 */
	void initialize();

	/**
	* Recreate the hole swap chain.
	*/
	void recreateSwapChain();

	/**
	 * Recreate the command buffers to update the geometry to be drawn.
	 */
	void recreateRenderingCommandBuffers();

	/**
	 * Cleanup swapchain elements. Can be used to clear the swapchain before recreating it using a diferent layout.
	 */
	void cleanupSwapChain();

	/** 
	 * Full cleanup of memory.
	 */
	void cleanup();

	/**
	 * Create a new vulkan instance.
	 */
	void createInstance();

	/**
	 * Setup debug callback.
	 */
	void setupDebugCallback();

	/**
	 * Create a window surface using GLFW.
	 */
	void createSurface();

	/**
	 * Choose a appropiate physical device to be used.
	 */
	void pickPhysicalDevice();

	/**
	 * Create a logical device using the physical device selected.
	 */
	void createLogicalDevice();

	/**
	 * Create the swap chain for rendering.
	 */
	void createSwapChain();

	/**
	 * Create image views.
	 */
	void createImageViews();

	/** 
	 * Create render pass (indicates where to read and write rendered data).
	 */
	void createRenderPass();

	/**
	 * Create descriptor set layout.
	 */
	void createDescriptorSetLayout();

	/** 
	 * Initializer graphics pipeline, load shaders, configure vertex format and rendering steps.
	 */
	void createGraphicsPipeline();

	/**
	 * Create frame buffers for the swap chain.
	 */
	void createFramebuffers();

	/**
	 * Create a command pool to send commands to the GPU.
	 */
	void createCommandPool(VkCommandPool *commandPool);

	/**
	 * Create vertex buffer.
	 */
	void createGeometryBuffers(Geometry *geometry);

	void createDescriptorPool();

	void createDescriptorSet();

	/**
	 * Handle image layout transitions
	 */
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

	/**
	 * Copy buffer to image helper (move to ImageUtils)
	 */
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

	/**
	 * Create texture image (move to ImageUtils)
	 */
	void createTextureImage(const char *fname);

	/**
	 * Create image view (generic) (move to ImageViewUtils maybe)
	 */
	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

	/**
	 * Create vulkan image and allocate memory for it (move to ImageUtils)
	 */
	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

	/**
	 * Depth buffer creation
	 */
	void createDepthResources();

	/**
	 * Check if the format for depth buffer has a stencil component
	 */
	bool hasStencilComponent(VkFormat format);

	/**
	 * Get depth buffer format
	 */
	VkFormat findDepthFormat();

	/**
	 * Check formats supported by the device from a vector of candidates
	 */
	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

	/**
	 * Create the actual draw command buffer
	 */
	void createRenderingCommandBuffers();

	/**
	 * Create syncronization semaphores and fences
	 */
	void createSyncObjects();

	/**
	 * Begin a single time use command buffer (Move to CommandBufferUtils)
	 */
	VkCommandBuffer beginSingleTimeCommands();

	/**
	 * End single time command buffer (Move to CommandBufferUtils)
	 */
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);

	/**
	 * Create a shader from SPIR-V code
	 */
	VkShaderModule createShaderModule(const std::vector<char>& code);

	/**
	 * Check if a device has all the required capabilities (is a discrete GPU and supports geometry shading).
	 */
	bool isPhysicalDeviceSuitable(VkPhysicalDevice physical);

	/**
	 * Check available device extensions
	 */
	bool checkDeviceExtensionSupport(VkPhysicalDevice physical);

	/**
	 * Choose swap chain format (color depth)
	 */
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

	/**
	 * Chose swap chain presentation mode
	 */
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);

	/**
	 * Choose resolution of the swap chain images (get it from the window size)
	 */
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	/**
	 * Check compatible swap chain support for our device
	 */
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice physical);

	/**
	 * Get required extensions if validation layers are active also add debug extension to the list
	 */
	std::vector<const char*> getRequiredExtensions();

	/**
	 * Check if validation layers are supported
	 */
	bool checkValidationLayerSupport();

	/**
	 * Debug callbacks
	 */
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData);
};

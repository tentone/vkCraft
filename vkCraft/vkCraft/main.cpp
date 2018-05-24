#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <iostream>
#include <vector>

const std::vector<const char*> validationLayers =
{
	"VK_LAYER_LUNARG_standard_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

//Declare the debug report extension
VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback)
{
	auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");

	if(func != nullptr)
	{
		return func(instance, pCreateInfo, pAllocator, pCallback);
	}
	else
	{
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

//Destroy the debug report extension
void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator)
{
	auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
	
	if(func != nullptr)
	{
		func(instance, callback, pAllocator);
	}
}

struct QueueFamilyIndices
{
	int graphicsFamily = -1;

	bool isComplete()
	{
		return graphicsFamily >= 0;
	}
};

//Main class
class VkCraft
{
public:
	void run()
	{
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}
private:
	GLFWwindow *window;
	VkInstance instance;
	VkDebugReportCallbackEXT callback;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device;
	VkQueue graphicsQueue;

	//Initialize GLFW window
	void initWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		window = glfwCreateWindow(800, 600, "VkCraft", nullptr, nullptr);
	}
	
	//Initialize vulkan
	void initVulkan()
	{
		//Create instance
		createInstance();
		
		//Prepare debug callbacks
		setupDebugCallback();
		
		//Pick a device
		pickPhysicalDevice();
		createLogicalDevice();
	}

	//Create a new vulkan instance
	void createInstance()
	{
		if(enableValidationLayers && !checkValidationLayerSupport())
		{
			throw std::runtime_error("validation layers requested, but not available!");
		}

		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "VkCraft";
		appInfo.pEngineName = "No Engine";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		std::vector<const char*> extensions = getRequiredExtensions();
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

		//Check extensions available
		std::cout << "GLFW Extensions:" << std::endl;
		for (uint32_t i = 0; i < extensions.size(); i++)
		{
			std::cout << extensions[i] << std::endl;
		}

		if(enableValidationLayers)
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else
		{
			createInfo.enabledLayerCount = 0;
		}

		if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create vulkan instance!");
		}

		//Check extensions available
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> vkExtensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, vkExtensions.data());
		
		std::cout << "Vulkan extensions:" << std::endl;
		for(uint32_t i = 0; i < vkExtensions.size(); i++)
		{
			std::cout << vkExtensions[i].extensionName << std::endl;
		}
	}
	
	//Choose a physical device
	void pickPhysicalDevice()
	{
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

		if(deviceCount == 0)
		{
			throw std::runtime_error("Not GPU with Vulkan support found!");
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

		for(const auto& device : devices)
		{
			if(isDeviceSuitable(device))
			{
				physicalDevice = device;
				break;
			}
		}

		if(physicalDevice == VK_NULL_HANDLE)
		{
			throw std::runtime_error("Could not find a suitable GPU!");
		}
	}

	//Check which queue families are supported by the device (we only need it to support graphics rendering)
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		int i = 0;
		for (const auto& queueFamily : queueFamilies)
		{
			if(queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				indices.graphicsFamily = i;
			}

			if (indices.isComplete())
			{
				break;
			}

			i++;
		}

		return indices;
	}

	//Check if a device has all the required capabilities (is a discrete GPU and supports geometry shading).
	bool isDeviceSuitable(VkPhysicalDevice device)
	{
		/*
		//Properties
		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);

		//Features
		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

		return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && deviceFeatures.geometryShader;
		*/

		QueueFamilyIndices indices = findQueueFamilies(device);
		return indices.isComplete();
	}

	//Create a logical device
	void createLogicalDevice()
	{
		QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = indices.graphicsFamily;
		queueCreateInfo.queueCount = 1;

		float queuePriority = 1.0f;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		VkPhysicalDeviceFeatures deviceFeatures = {};

		VkDeviceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = &queueCreateInfo;
		createInfo.queueCreateInfoCount = 1;
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = 0;

		if(enableValidationLayers)
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else
		{
			createInfo.enabledLayerCount = 0;
		}

		if(vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create the logical device!");
		}

		vkGetDeviceQueue(device, indices.graphicsFamily, 0, &graphicsQueue);
	}

	//Setup debug callback
	void setupDebugCallback()
	{
		if(!enableValidationLayers)
		{
			return;
		}

		VkDebugReportCallbackCreateInfoEXT createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
		createInfo.pfnCallback = debugCallback;

		if(CreateDebugReportCallbackEXT(instance, &createInfo, nullptr, &callback) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to set up debug callback!");
		}
	}

	//Get required extensions if validation layers are active also add debug extension to the list
	std::vector<const char*> getRequiredExtensions()
	{
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (enableValidationLayers)
		{
			extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		}

		return extensions;
	}

	//Logic loop
	void mainLoop()
	{
		while(!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
		}
	}
	
	//Cleanup memory
	void cleanup()
	{
		std::cout << "Cleanup" << std::endl;

		//Device
		vkDestroyDevice(device, nullptr);
		
		//Vulkan instance
		vkDestroyInstance(instance, nullptr);

		//Window
		glfwDestroyWindow(window);
		glfwTerminate();

		//If validation layers are enabled destroy debug callback
		if(enableValidationLayers)
		{
			DestroyDebugReportCallbackEXT(instance, callback, nullptr);
		}
	}

	//Check if validation layers are supported
	bool checkValidationLayerSupport()
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : validationLayers)
		{
			bool layerFound = false;

			for (const auto& layerProperties : availableLayers)
			{
				if (strcmp(layerName, layerProperties.layerName) == 0)
				{
					layerFound = true;
					break;
				}
			}

			if (!layerFound)
			{
				return false;
			}
		}

		return true;
	}

	//Debug callbacks
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData)
	{
		std::cerr << "validation layer: " << msg << std::endl;

		return VK_FALSE;
	}
};

//Main entry point
int main()
{
	VkCraft app;

	try
	{
		app.run();
	}
	catch(const std::runtime_error &error)
	{
		std::cerr << error.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

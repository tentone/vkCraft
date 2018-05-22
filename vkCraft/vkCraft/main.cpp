#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <iostream>
#include <vector>

class VkCraft
{
public:
	void run()
	{
		initWindow();
		initVulkan();
		//mainLoop();
		cleanup();
	}
private:
	GLFWwindow * window;
	VkInstance instance;
	
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
		createInstance();
	}

	//Create a new vulkan instance
	void createInstance()
	{
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
		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;

		if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create vulkan instance!");
		}
		
		//Check extensions available
		uint32_t extensionCount = 0;
		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

		for(uint32_t i = 0; i < extensions.size(); i++)
		{
			std::cout << "\n" << extensions[i].extensionName << std::endl;
		}
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

		//Vulkan instance
		vkDestroyInstance(instance, nullptr);

		//Window
		glfwDestroyWindow(window);
		glfwTerminate();
	}
};

int main()
{
	VkCraft app;

	try
	{
		app.run();
	}
	catch (const std::runtime_error &error)
	{
		std::cerr << error.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

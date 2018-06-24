#pragma once

#include "VkCraft.cpp"

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

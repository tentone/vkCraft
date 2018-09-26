#pragma once

/*
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif
*/

#include <cstdlib>
#include "VkCraft.h"

int main()
{
	//_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	VkCraft app;
	
	try
	{
		app.run();

	}
	catch (const std::runtime_error &error)
	{
		std::cerr << "vkCraft: " << error.what() << std::endl;
		return EXIT_FAILURE;
	}
	
	//_CrtDumpMemoryLeaks();

	return EXIT_SUCCESS;
}

#pragma once

class QueueFamilyIndices
{
public:
	int graphicsFamily = -1;
	int presentFamily = -1;

	bool isComplete();
};
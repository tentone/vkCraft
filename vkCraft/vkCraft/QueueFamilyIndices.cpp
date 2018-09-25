#pragma once

#include "QueueFamilyIndices.h"

bool QueueFamilyIndices::isComplete()
{
	return graphicsFamily >= 0 && presentFamily >= 0;
}

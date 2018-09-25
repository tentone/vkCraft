#pragma once

#include <vector>
#include "Geometry.h"
#include "Vertex.h"

class PlaneGeometry : public Geometry
{
public:
	void generate()
	{
		vertices =
		{
			{ { -1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
			{ { 1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f } },
			{ { 1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
			{ { -1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } }
		};

		indices =
		{
			0, 1, 2, 2, 3, 0
		};
	}
};
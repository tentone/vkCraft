#pragma once

#include <vector>
#include "Geometry.cpp"
#include "Vertex.cpp"

class PlaneGeometry : public Geometry
{
public:
	void generate(Device *device, VkQueue *graphicsQueue, VkCommandPool *commandPool)
	{
		std::vector<uint32_t> indices;
		std::vector<Vertex> vertices;

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

		createGeometryBuffers(device, graphicsQueue, commandPool, &indices, &vertices);
	}
};
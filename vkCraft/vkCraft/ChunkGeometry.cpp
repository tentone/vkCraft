#pragma once

#include <vector>
#include "Geometry.cpp"
#include "Vertex.cpp"

class ChunkGeometry : public Geometry
{
public:
	void generate()
	{
		vertices = {};

		indices = {};
	}
};
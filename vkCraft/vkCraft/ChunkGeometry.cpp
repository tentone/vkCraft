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
		
		for (unsigned int x = 0; x < 32; x++)
		{
			for (unsigned int y = 0; y < 32; y++)
			{
				
			}
		}
		//vertices.push_back();

		indices = {};
	}
};
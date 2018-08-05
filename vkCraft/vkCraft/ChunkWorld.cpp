#pragma once

#include <vector>

#include "ChunkGeometry.cpp"

class ChunkWorld
{
public:
	std::vector<ChunkGeometry*> chunks;

	ChunkWorld()
	{
		
	}

	void generateChunks()
	{
	}
};
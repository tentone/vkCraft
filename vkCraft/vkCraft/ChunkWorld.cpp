#pragma once

#include <vector>

#include "Chunk.cpp"

class ChunkWorld
{
public:
	std::vector<Chunk> chunks;
	double waterLevel = 0.0f;

	ChunkWorld()
	{
		
	}
};
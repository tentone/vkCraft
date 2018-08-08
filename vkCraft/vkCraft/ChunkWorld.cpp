#pragma once

#include <vector>

#include "ChunkGeometry.cpp"

class ChunkWorld
{
public:
	std::vector<std::vector<std::vector<Chunk*>>> chunks;

	void generateChunks()
	{

	}
};
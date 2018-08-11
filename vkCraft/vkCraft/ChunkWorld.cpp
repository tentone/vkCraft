#pragma once

#include "ChunkNode.cpp"

/**
 * Chunk world is used to access and manipulate chunk data.
 *
 * It automatically generates missing data on request.
 */
class ChunkWorld
{
public:
	
	/**
	 * Root chunk position in the world origin.
	 */
	ChunkNode *root;

	/**
	 * World seed, used to generate exactly the same world every time.
	 */
	int seed;

	/**
	 * Chunk world constructor creates the root chunk.
	 */
	ChunkWorld(int _seed)
	{
		seed = _seed;

		root = new ChunkNode(glm::ivec3(0, 0, 0));
		root->generateChunk(seed);
		root->generateGeometry();
	}
};
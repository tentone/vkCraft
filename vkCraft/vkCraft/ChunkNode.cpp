#pragma once

#include "Chunk.cpp"
#include "ChunkGeometry.cpp"

class ChunkNode
{
public:
	/**
	 * Uninitiaalized state, the node has no chunk data and geometry.
	 */
	static const int UNINITIALIZED = 0;

	/**
	 * The node only has chunk data.
	 */
	static const int DATA = 1;

	/**
	 * The node and chunk and geometry data.
	 */
	static const int GEOMETRY = 2;

	/**
	 * Geometry to represent this chunk.
	 */
	Chunk *chunk;

	/**
	 * Geometry to represent this chunk.
	 */
	ChunkGeometry *geometry;
	
	/**
	 * Node state.
	 */
	int state;

	/**
	 * Pointer to neighboor chunks.
	 *
	 * left is -x, right +x
	 * front is +z, back is -z
	 * up is +y, down is -y
	 */
	Chunk *left, *right, *front, *back, *up, *down;

	ChunkNode(glm::ivec3 position)
	{
		state = UNINITIALIZED;
		chunk = new Chunk(position);
		geometry = new ChunkGeometry(chunk);
	}

	/**
	* Generate data for this node.
	*/
	void generateChunk(int seed)
	{
		state = DATA;
		chunk->generate(seed);
	}

	/**
	 * Generate geometry for this node.
	 */
	void generateGeometry()
	{
		state = GEOMETRY;
		geometry->generate();
	}
};


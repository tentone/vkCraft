#pragma once

#include "Chunk.cpp"
#include "ChunkGeometry.cpp"

class ChunkNode
{
public:
	/**
	 * Disposed node.
	 */
	static const int DISPOSED = -1;

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
	* The geometry buffers are created
	*/
	static const int READY = 3;

	/*
	 * left is - x, right + x
	 * front is + z, back is - z
	 * up is + y, down is - y
	 */
	static const int LEFT = 0;
	static const int RIGHT = 1;
	static const int FRONT = 2;
	static const int BACK = 3;
	static const int UP = 4;
	static const int DOWN = 5;

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
	 * Node index relataive to the root.
	 */
	glm::ivec3 index;

	/**
	 * Numeric timestamp, that can be compared with a world timestamp and updated on generation.
	 *
	 * Can be used to avoid recursive propagation of updates in nodes.
	 */
	int timestamp = -1;

	/**
	 * Pointer to neighboor chunks.
	 */
	ChunkNode *neighbors[6];

	/**
	 * Node constructor.
	 */
	ChunkNode(glm::ivec3 _index)
	{
		index = _index;
		state = UNINITIALIZED;
		chunk = new Chunk(_index);
		geometry = new ChunkGeometry(chunk);

		for (unsigned int i = 0; i < 6; i++)
		{
			neighbors[i] = nullptr;
		}
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
		if (state < DATA)
		{
			return;
		}

		state = GEOMETRY;
		geometry->generate();
	}

	/**
	* Dispose all the geometries attached to the nodes in this world.
	*/
	void dispose(VkDevice *device)
	{
		if (state >= GEOMETRY)
		{
			geometry->dispose(device);
		}
		
		state = DISPOSED;

		//Dipose neighboors
		for (unsigned int i = 0; i < 6; i++)
		{
			if(neighbors[i] != nullptr && neighbors[i]->state != DISPOSED)
			{
				neighbors[i]->dispose(device);
			}
		}
	}
};


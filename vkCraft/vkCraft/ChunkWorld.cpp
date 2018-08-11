#pragma once

#include <vector>

#include "Device.cpp"
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
	 * Vector of geometries visible for this world.
	 *
	 * The geometries are updated using the updateGeometries() method.
	 */
	std::vector<Geometry*> geometries;

	/**
	 * Current chunk, was the chunk used as center in the last update.
	 */
	ChunkNode *current;

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

	/**
	 * Update world chunks based on position.
	 *
	 * If there are no chunk available new chunks will be created.
	 */
	void updateGeometries(glm::vec3 position, int distance)
	{
		glm::ivec3 index = { position.x / Chunk::SIZE, position.y / Chunk::SIZE , position.z / Chunk::SIZE };
		
		geometries.clear();
		geometries.push_back(root->geometry);

		//TODO <UPDATE CHUNKS>
	}

	/**
	 * Get chunk from its index.
	 */
	ChunkNode* getChunkNode(glm::ivec3 index)
	{
		//TODO <ADD CODE HERE>
	}

	/**
	 * Get block for a specific position.
	 */
	void getBlock(glm::ivec3 position)
	{
		glm::ivec3 index = { position.x / Chunk::SIZE, position.y / Chunk::SIZE , position.z / Chunk::SIZE };
		ChunkNode *node = getChunkNode(index);

		//TODO <ADD CODE>
	}

	/**
	 * Dispose all the geometries attached to the nodes in this world.
	 */
	void dispose(VkDevice *device)
	{
		root->dispose(device);
	}
};
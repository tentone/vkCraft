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

		root = new ChunkNode(glm::ivec3(0, 0, 0), seed);
		root->generateNeighbors(6);
	}

	/**
	 * Update world chunks based on position.
	 *
	 * If there are no chunk available new chunks will be created.
	 */
	std::vector<Geometry*> getGeometries(glm::vec3 position, int distance)
	{
		glm::ivec3 index = { position.x / Chunk::SIZE, position.y / Chunk::SIZE , position.z / Chunk::SIZE };
		
		//Clear geometries vector
		geometries.clear();

		//Get node
		ChunkNode *node = getChunkNode(index);
		node->getGeometries(&geometries, distance);

		return geometries;
	}

	/**
	 * Get chunk from its index.
	 */
	ChunkNode* getChunkNode(glm::ivec3 index)
	{
		
		/*for (int x = 0; x < index.x; x++)
		{
			for (int y = 0; y < index.y; y++)
			{
				for (int z = 0; x < index.z; z++)
				{

				}
			}
		}*/

		return root;
	}

	/**
	 * Get block for a specific position.
	 */
	int getBlock(glm::ivec3 position)
	{
		glm::ivec3 index = { position.x / Chunk::SIZE, position.y / Chunk::SIZE , position.z / Chunk::SIZE };
		ChunkNode *node = getChunkNode(index);

		//TODO <ADD CODE>

		return -1;
	}

	/**
	 * Dispose all the geometries attached to the nodes in this world.
	 */
	void dispose(VkDevice *device)
	{
		root->dispose(device);
	}
};
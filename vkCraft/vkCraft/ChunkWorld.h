#pragma once

#include <vector>
#include <math.h>

#include "Device.h"
#include "Geometry.h"
#include "ChunkNode.h"

class ChunkNode;

/**
 * Chunk world is used to access and manipulate chunk data.
 *
 * It automatically generates missing data on request.
 */
class ChunkWorld
{
private:
	ChunkNode *current;
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
	 * Chunk world constructor creates the root chunk.
	 */
	ChunkWorld(int _seed);

	/**
	 * Get world index from world position.
	 */
	glm::ivec3 getIndex(glm::vec3 position);

	/**
	 * Update world chunks based on position.
	 *
	 * If there are no chunk available new chunks will be created.
	 */
	std::vector<Geometry*> getGeometries(glm::vec3 position, int distance);

	/**
	 * Get chunk from its index.
	 */
	ChunkNode* getChunkNode(glm::ivec3 index);

	/**
	 * Get block for a specific world position.
	 *
	 * Gets the node that stores that position and the block value.
	 */
	int getBlock(glm::ivec3 position);

	/**
	 * Dispose all the geometries attached to the nodes in this world.
	 *
	 * Nodes ares disposed recursively.
	 */
	void dispose(VkDevice &device);
};
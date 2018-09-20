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
	ChunkWorld(int _seed)
	{
		seed = _seed;

		root = new ChunkNode(glm::ivec3(0, 0, 0), seed);
		current = root;
	}

	/**
	 * Update world chunks based on position.
	 *
	 * If there are no chunk available new chunks will be created.
	 */
	std::vector<Geometry*> getGeometries(glm::vec3 position, Device *device, VkQueue *graphicsQueue, VkCommandPool *commandPool, int distance)
	{
		glm::ivec3 index = { position.x / Chunk::SIZE, position.y / Chunk::SIZE , position.z / Chunk::SIZE };
		
		//Clear geometries vector
		geometries.clear();

		//Get node
		ChunkNode *node = getChunkNode(index);

		node->getGeometries(&geometries, device, graphicsQueue, commandPool, distance);

		return geometries;
	}

	/**
	 * Get chunk from its index.
	 */
	ChunkNode* getChunkNode(glm::ivec3 index)
	{
		//std::cout << "vkCraft: Requested chunk: " << index.x << ", " << index.y << ", " << index.z << std::endl;

		glm::ivec3 offset = current->index - index;
		//std::cout << "vkCraft: Chunk offset: " << offset.x << ", " << offset.y << ", " << offset.z << std::endl;

		//X
		if (offset.x > 0)
		{
			for (int x = 0; x < offset.x; x++)
			{
				if (current->neighbors[ChunkNode::LEFT] == nullptr)
				{
					current->generateNeighbors();
				}

				current = current->neighbors[ChunkNode::LEFT];
			}
		}
		else if (offset.x < 0)
		{
			for (int x = offset.x; x < 0; x++)
			{
				if (current->neighbors[ChunkNode::RIGHT] == nullptr)
				{
					current->generateNeighbors();
				}

				current = current->neighbors[ChunkNode::RIGHT];
			}
		}

		//Y
		if (offset.y > 0)
		{
			for (int y = 0; y < offset.y; y++)
			{
				if (current->neighbors[ChunkNode::DOWN] == nullptr)
				{
					current->generateNeighbors();
				}

				current = current->neighbors[ChunkNode::DOWN];
			}
		}
		else if (offset.y < 0)
		{
			for (int y = offset.y; y < 0; y++)
			{
				if (current->neighbors[ChunkNode::UP] == nullptr)
				{
					current->generateNeighbors();
				}

				current = current->neighbors[ChunkNode::UP];
			}
		}

		//Z
		if (offset.z > 0)
		{
			for (int z = 0; z < offset.z; z++)
			{
				if (current->neighbors[ChunkNode::FRONT] == nullptr)
				{
					current->generateNeighbors();
				}

				current = current->neighbors[ChunkNode::FRONT];
			}
		}
		else if (offset.z < 0)
		{
			for (int z = offset.z; z < 0; z++)
			{
				if (current->neighbors[ChunkNode::BACK] == nullptr)
				{
					current->generateNeighbors();
				}

				current = current->neighbors[ChunkNode::BACK];
			}
		}

		//std::cout << "vkCraft: Obtained chunk: " << current->index.x << ", " << current->index.y << ", " << current->index.z << std::endl;

		return current;
	}

	/**
	 * Get block for a specific world position.
	 *
	 * Gets the node that stores that position and the block value.
	 */
	int getBlock(glm::ivec3 position)
	{
		glm::ivec3 index = { position.x / Chunk::SIZE, position.y / Chunk::SIZE , position.z / Chunk::SIZE };
		ChunkNode *node = getChunkNode(index);

		return node->chunk.data[position.x % Chunk::SIZE][position.y % Chunk::SIZE][position.z % Chunk::SIZE];
	}

	/**
	 * Dispose all the geometries attached to the nodes in this world.
	 *
	 * Nodes ares disposed recursively.
	 */
	void dispose(VkDevice &device)
	{
		root->dispose(device);
		delete root;
	}
};
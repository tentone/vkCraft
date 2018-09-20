#pragma once

#include "Chunk.cpp"
#include "ChunkGeometry.cpp"

#include <algorithm>

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

	/*
	 * left is - x, right + x
	 * front is - z, back is + z
	 * up is + y, down is - y
	 */
	static const int LEFT = 0;
	static const int RIGHT = 1;
	static const int FRONT = 2;
	static const int BACK = 3;
	static const int UP = 4;
	static const int DOWN = 5;

	/**
	 * Chunk data.
	 */
	Chunk chunk;

	/**
	 * Geometry to represent this chunk.
	 */
	ChunkGeometry geometry;
	
	/**
	 * Node state.
	 */
	int state;
	
	/**
	 * World seed.
	 */
	int seed;

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
	ChunkNode *neighbors[6] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

	ChunkNode(glm::ivec3 _index, int _seed)
	{
		index = _index;
		state = UNINITIALIZED;
		chunk.setIndex(_index);
		generateData();
	}

	/**
	 * Get geometries from this node and its neighboors recursively.
	 */
	void getGeometries(std::vector<Geometry*> *geometries, Device *device, VkQueue *graphicsQueue, VkCommandPool *commandPool, int recursive = 0)
	{
		//Generate geometry if necessary
		if(state < GEOMETRY)
		{
			generateGeometry(device, graphicsQueue, commandPool);
		}

		//Check if geometries contains geometry, it it does not add new
		if (std::find(geometries->begin(), geometries->end(), &geometry) == geometries->end())
		{
			geometries->push_back(&geometry);
		}
		else
		{
			return;
		}

		if (recursive > 0)
		{
			generateNeighbors();

			for (unsigned int i = 0; i < 6; i++)
			{
				neighbors[i]->getGeometries(geometries, device, graphicsQueue, commandPool, recursive - 1);
			}
		}
	}

	/**
	 * Generate neighbors for a node.
	 */
	void generateNeighbors(int recursive = 0)
	{
		//X
		if (neighbors[ChunkNode::LEFT] == nullptr)
		{
			neighbors[ChunkNode::LEFT] = new ChunkNode(glm::ivec3(index.x - 1, index.y, index.z), seed);
			neighbors[ChunkNode::LEFT]->neighbors[ChunkNode::RIGHT] = this;
		}
		if (neighbors[ChunkNode::RIGHT] == nullptr)
		{
			neighbors[ChunkNode::RIGHT] = new ChunkNode(glm::ivec3(index.x + 1, index.y, index.z), seed);
			neighbors[ChunkNode::RIGHT]->neighbors[ChunkNode::LEFT] = this;
		}

		//Y
		if (neighbors[ChunkNode::UP] == nullptr)
		{
			neighbors[ChunkNode::UP] = new ChunkNode(glm::ivec3(index.x, index.y + 1, index.z), seed);
			neighbors[ChunkNode::UP]->neighbors[ChunkNode::DOWN] = this;
		}
		if (neighbors[ChunkNode::DOWN] == nullptr)
		{
			neighbors[ChunkNode::DOWN] = new ChunkNode(glm::ivec3(index.x, index.y - 1, index.z), seed);
			neighbors[ChunkNode::DOWN]->neighbors[ChunkNode::UP] = this;
		}

		//Z
		if (neighbors[ChunkNode::FRONT] == nullptr)
		{
			neighbors[ChunkNode::FRONT] = new ChunkNode(glm::ivec3(index.x, index.y, index.z - 1), seed);
			neighbors[ChunkNode::FRONT]->neighbors[ChunkNode::BACK] = this;
		}
		if (neighbors[ChunkNode::BACK] == nullptr)
		{
			neighbors[ChunkNode::BACK] = new ChunkNode(glm::ivec3(index.x, index.y, index.z + 1), seed);
			neighbors[ChunkNode::BACK]->neighbors[ChunkNode::FRONT] = this;
		}

		if (recursive > 0)
		{
			for (unsigned int i = 0; i < 6; i++)
			{
				neighbors[i]->generateNeighbors(recursive - 1);
			}
		}
	}

	/**
	* Generate data for this node.
	*/
	void generateData()
	{
		state = DATA;
		chunk.generate(seed);
	}

	/**
	 * Generate geometry for this node.
	 */
	void generateGeometry(Device *device, VkQueue *graphicsQueue, VkCommandPool *commandPool)
	{
		//If it still has no chunk data generate it
		if (state < DATA)
		{
			generateData();
		}

		state = GEOMETRY;
		geometry.generate(&chunk, device, graphicsQueue, commandPool);
	}

	/**
	 * Dispose all the geometries attached to this node recursively.
	 */
	void dispose(VkDevice &device)
	{
		//Check if the geometry has buffers
		if (state > DATA)
		{
			geometry.dispose(device);
			state = DATA;
		}
		
		//Dipose neighboors
		for (unsigned int i = 0; i < 6; i++)
		{
			if(neighbors[i] != nullptr && neighbors[i]->state > DATA)
			{
				neighbors[i]->dispose(device);
				delete neighbors[i];
			}
		}
	}
};


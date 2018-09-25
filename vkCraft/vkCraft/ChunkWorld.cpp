#pragma once

#include "ChunkWorld.h"

ChunkWorld::ChunkWorld(int _seed)
{
	seed = _seed;

	root = new ChunkNode(glm::ivec3(0, 0, 0), seed);
	current = root;
}
	

glm::ivec3 ChunkWorld::getIndex(glm::vec3 position)
{
	return { position.x / Chunk::SIZE, position.y / Chunk::SIZE , position.z / Chunk::SIZE };
}

std::vector<Geometry*> ChunkWorld::getGeometries(glm::vec3 position, int distance)
{
	glm::ivec3 index = getIndex(position);
	geometries.clear();

	ChunkNode *node = getChunkNode(index);
	node->getGeometries(&geometries, this, distance);

	return geometries;
}

ChunkNode* ChunkWorld::getChunkNode(glm::ivec3 index)
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

int ChunkWorld::getBlock(glm::ivec3 position)
{
	ChunkNode *node = getChunkNode(getIndex(position));

	return node->chunk.data[position.x % Chunk::SIZE][position.y % Chunk::SIZE][position.z % Chunk::SIZE];
}

void ChunkWorld::dispose(VkDevice &device)
{
	root->dispose(device);
	delete root;
}

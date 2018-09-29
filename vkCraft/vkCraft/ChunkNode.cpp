#pragma once

#include "ChunkNode.h"

ChunkNode::ChunkNode(glm::ivec3 _index, int _seed)
{
	index = _index;
	state = UNINITIALIZED;
	chunk.setIndex(_index);
	geometry = new ChunkGeometry();
	generateData();
}

void ChunkNode::getGeometries(std::vector<Geometry*> *geometries, ChunkWorld *world, int recursive)
{
	//Generate geometry if necessary
	if(state < GEOMETRY)
	{
		generateGeometry(world);
	}

	//Check if geometries contains geometry, it it does not add new
	if (std::find(geometries->begin(), geometries->end(), geometry) == geometries->end())
	{
		geometries->push_back(geometry);
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
			neighbors[i]->getGeometries(geometries, world, recursive - 1);
		}
	}
}

void ChunkNode::generateNeighbors(int recursive)
{
	searchNeighbors();

	//X - 1 Left
	if (neighbors[ChunkNode::LEFT] == nullptr)
	{
		neighbors[ChunkNode::LEFT] = new ChunkNode(glm::ivec3(index.x - 1, index.y, index.z), seed);
		neighbors[ChunkNode::LEFT]->neighbors[ChunkNode::RIGHT] = this;
	}
	//X + 1 Right
	if (neighbors[ChunkNode::RIGHT] == nullptr)
	{
		neighbors[ChunkNode::RIGHT] = new ChunkNode(glm::ivec3(index.x + 1, index.y, index.z), seed);
		neighbors[ChunkNode::RIGHT]->neighbors[ChunkNode::LEFT] = this;
	}

	//Y + 1 Up
	if (neighbors[ChunkNode::UP] == nullptr)
	{
		neighbors[ChunkNode::UP] = new ChunkNode(glm::ivec3(index.x, index.y + 1, index.z), seed);
		neighbors[ChunkNode::UP]->neighbors[ChunkNode::DOWN] = this;
	}
	//Y - 1 Down
	if (neighbors[ChunkNode::DOWN] == nullptr)
	{
		neighbors[ChunkNode::DOWN] = new ChunkNode(glm::ivec3(index.x, index.y - 1, index.z), seed);
		neighbors[ChunkNode::DOWN]->neighbors[ChunkNode::UP] = this;
	}

	//Z - 1 Front
	if (neighbors[ChunkNode::FRONT] == nullptr)
	{
		neighbors[ChunkNode::FRONT] = new ChunkNode(glm::ivec3(index.x, index.y, index.z - 1), seed);
		neighbors[ChunkNode::FRONT]->neighbors[ChunkNode::BACK] = this;
	}
	//Z + 1 Back
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

void ChunkNode::searchNeighbors()
{
	int a[3] = { ChunkNode::RIGHT, ChunkNode::FRONT, ChunkNode::LEFT };
	ChunkNode::fetchNeighborPath(a, 3, ChunkNode::FRONT);

	int b[3] = { ChunkNode::RIGHT, ChunkNode::BACK, ChunkNode::LEFT };
	ChunkNode::fetchNeighborPath(b, 3, ChunkNode::BACK);

	int c[3] = { ChunkNode::RIGHT, ChunkNode::UP, ChunkNode::LEFT };
	ChunkNode::fetchNeighborPath(c, 3, ChunkNode::UP);

	int d[3] = { ChunkNode::RIGHT, ChunkNode::DOWN, ChunkNode::LEFT };
	ChunkNode::fetchNeighborPath(d, 3, ChunkNode::DOWN);

	//Right if known (try to get front, back, top, down)
	if (neighbors[ChunkNode::FRONT] != nullptr)
	{
		if (neighbors[ChunkNode::RIGHT]->neighbors[ChunkNode::FRONT] != nullptr && neighbors[ChunkNode::RIGHT]->neighbors[ChunkNode::FRONT]->neighbors[ChunkNode::LEFT] != nullptr)
		{
			neighbors[ChunkNode::FRONT] = neighbors[ChunkNode::RIGHT]->neighbors[ChunkNode::FRONT]->neighbors[ChunkNode::LEFT];
			std::cout << "VkCraft: Found F node from (R->F->L) (" << neighbors[ChunkNode::FRONT]->index.x << ", " << neighbors[ChunkNode::FRONT]->index.y << ", " << neighbors[ChunkNode::FRONT]->index.z << ")" << std::endl;
		}

		if (neighbors[ChunkNode::RIGHT]->neighbors[ChunkNode::BACK] != nullptr && neighbors[ChunkNode::RIGHT]->neighbors[ChunkNode::BACK]->neighbors[ChunkNode::LEFT] != nullptr)
		{
			neighbors[ChunkNode::BACK] = neighbors[ChunkNode::RIGHT]->neighbors[ChunkNode::BACK]->neighbors[ChunkNode::LEFT];
			std::cout << "VkCraft: Found B node from (R->B->L) (" << neighbors[ChunkNode::BACK]->index.x << ", " << neighbors[ChunkNode::BACK]->index.y << ", " << neighbors[ChunkNode::BACK]->index.z << ")" << std::endl;
		}

		if (neighbors[ChunkNode::RIGHT]->neighbors[ChunkNode::UP] != nullptr && neighbors[ChunkNode::RIGHT]->neighbors[ChunkNode::UP]->neighbors[ChunkNode::LEFT] != nullptr)
		{
			neighbors[ChunkNode::UP] = neighbors[ChunkNode::RIGHT]->neighbors[ChunkNode::UP]->neighbors[ChunkNode::LEFT];
			std::cout << "VkCraft: Found U node from (R->U->L) (" << neighbors[ChunkNode::UP]->index.x << ", " << neighbors[ChunkNode::UP]->index.y << ", " << neighbors[ChunkNode::UP]->index.z << ")" << std::endl;
		}

		if (neighbors[ChunkNode::RIGHT]->neighbors[ChunkNode::DOWN] != nullptr && neighbors[ChunkNode::RIGHT]->neighbors[ChunkNode::DOWN]->neighbors[ChunkNode::LEFT] != nullptr)
		{
			neighbors[ChunkNode::DOWN] = neighbors[ChunkNode::RIGHT]->neighbors[ChunkNode::DOWN]->neighbors[ChunkNode::LEFT];
			std::cout << "VkCraft: Found D node from (R->D->L) (" << neighbors[ChunkNode::DOWN]->index.x << ", " << neighbors[ChunkNode::DOWN]->index.y << ", " << neighbors[ChunkNode::DOWN]->index.z << ")" << std::endl;
		}
	}

	/*
	if (neighbors[ChunkNode::FRONT] != nullptr && neighbors[ChunkNode::FRONT]->neighbors[ChunkNode::LEFT] != nullptr)
	{
		neighbors[ChunkNode::LEFT]->neighbors[ChunkNode::FRONT] = neighbors[ChunkNode::FRONT]->neighbors[ChunkNode::LEFT];
	}

	if (neighbors[ChunkNode::BACK] != nullptr && neighbors[ChunkNode::BACK]->neighbors[ChunkNode::LEFT] != nullptr)
	{
		neighbors[ChunkNode::LEFT]->neighbors[ChunkNode::BACK] = neighbors[ChunkNode::BACK]->neighbors[ChunkNode::LEFT];
	}
	*/
}

void ChunkNode::fetchNeighborPath(int path[], int length, int position)
{
	ChunkNode *node = getNeighborPath(path, length);

	if (node != nullptr)
	{
		if (neighbors[position] == nullptr)
		{
			neighbors[position] = node;
		}
		else
		{
			std::cout << "VkCraft: fetchNeighborPath " << position << " already has a node stored." << std::endl;
		}
	}
}

ChunkNode* ChunkNode::getNeighborPath(int path[], int length)
{
	//std::cout << "VkCraft: getNeighborPath path length " << length << ", " << sizeof(path) << ", " << sizeof(int) << std::endl;

	if (length < 1 || neighbors[path[0]] == nullptr)
	{
		return nullptr;
	}

	ChunkNode* node = neighbors[path[0]];

	for (int i = 1; i < length; i++)
	{
		if (node->neighbors[path[i]] != nullptr)
		{
			node = node->neighbors[path[i]];
		}
		else
		{
			return nullptr;
		}
	}

	std::cout << "VkCraft: Found node ";
	for (int i = 0; i < length; i++)
	{
		std::cout << path[i] << ", ";
	}
	std::cout << std::endl;

	return node;
}

void ChunkNode::generateData()
{
	state = DATA;
	chunk.generate(seed);
}

void ChunkNode::generateGeometry(ChunkWorld *world)
{
	//If it still has no chunk data generate it
	if (state < DATA)
	{
		generateData();
	}

	state = GEOMETRY;
	geometry->generate(&chunk, world);
}

void ChunkNode::dispose(VkDevice &device)
{
	//Check if the geometry has buffers
	if (state > DATA)
	{
		geometry->dispose(device);
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

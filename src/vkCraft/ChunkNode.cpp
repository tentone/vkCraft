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

void ChunkNode::getNodes(std::vector<ChunkNode*> *nodes, int recursive)
{
	bool found = false;
	for (unsigned int i = 0; i < nodes->size(); i++)
	{
		if ((*nodes)[i]->index == index)
		{
			found = true;
			break;
		}
	}
	
	if (found == false)
	{
		nodes->push_back(this);
	}

	if (recursive > 0)
	{
		generateNeighbors();

		for (unsigned int i = 0; i < 6; i++)
		{
			neighbors[i]->getNodes(nodes, recursive - 1);
		}
	}
}

Geometry* ChunkNode::getGeometry(ChunkWorld *world)
{
	if (state < GEOMETRY)
	{
		generateGeometry(world);
	}

	return geometry;
}

void ChunkNode::getGeometries(std::vector<Geometry*> *geometries, ChunkWorld *world, int recursive)
{
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
	std::vector<ChunkNode*> nodes = std::vector<ChunkNode*>();

	if (neighbors[ChunkNode::LEFT] == nullptr)
	{
		nodes.clear();
		ChunkNode* left = searchNode({index.x - 1, index.y, index.z}, &nodes);
		if (left != nullptr)
		{
			neighbors[ChunkNode::LEFT] = left;
		}
	}
	
	if (neighbors[ChunkNode::RIGHT] == nullptr)
	{
		nodes.clear();
		ChunkNode* right = searchNode({ index.x + 1, index.y, index.z }, &nodes);
		if (right != nullptr)
		{
			neighbors[ChunkNode::RIGHT] = right;
		}
	}

	if (neighbors[ChunkNode::FRONT] == nullptr)
	{
		nodes.clear();
		ChunkNode* front = searchNode({ index.x, index.y, index.z - 1}, &nodes);
		if (front != nullptr)
		{
			neighbors[ChunkNode::FRONT] = front;
		}
	}
	if (neighbors[ChunkNode::BACK] == nullptr)
	{
		nodes.clear();
		ChunkNode* back = searchNode({ index.x, index.y, index.z + 1}, &nodes);
		if (back != nullptr)
		{
			neighbors[ChunkNode::BACK] = back;
		}
	}

	if (neighbors[ChunkNode::UP] == nullptr)
	{
		nodes.clear();
		ChunkNode* up = searchNode({ index.x, index.y + 1, index.z }, &nodes);
		if (up != nullptr)
		{
			neighbors[ChunkNode::UP] = up;
		}
	}

	if (neighbors[ChunkNode::DOWN] == nullptr)
	{
		nodes.clear();
		ChunkNode* down = searchNode({ index.x, index.y - 1, index.z }, &nodes);
		if (down != nullptr)
		{
			neighbors[ChunkNode::DOWN] = down;
		}
	}
	
}

ChunkNode* ChunkNode::searchNode(glm::ivec3 index, std::vector<ChunkNode*> *nodes)
{
	if (std::find(nodes->begin(), nodes->end(), this) != nodes->end())
	{
		return nullptr;
	}

	nodes->push_back(this);
	
	//Check if it is one of its neighbors
	for (unsigned int i = 0; i < 6; i++)
	{
		if (neighbors[i] != nullptr && neighbors[i]->index == index)
		{
			return neighbors[i];
		}
	}

	//Recursively search neighbors
	for (unsigned int i = 0; i < 6; i++)
	{
		if (neighbors[i] != nullptr)
		{
			ChunkNode* node = neighbors[i]->searchNode(index, nodes);
			if (node != nullptr)
			{
				return node;
			}
		}
	}

	return nullptr;
}

ChunkNode* ChunkNode::getNeighborPath(int path[], int size)
{
	if (size < 1 || neighbors[path[0]] == nullptr)
	{
		return nullptr;
	}

	ChunkNode* node = neighbors[path[0]];

	for (int i = 1; i < size; i++)
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

	return node;
}

void ChunkNode::generateData()
{
	state = DATA;
	chunk.generate(seed);
}

void ChunkNode::generateGeometry(ChunkWorld *world)
{
	if (state < DATA)
	{
		generateData();
	}

	state = GEOMETRY;
	geometry->generate(&chunk, world);
}

void ChunkNode::dispose(VkDevice &device)
{
	if (state > DATA)
	{
		geometry->dispose(device);
		state = DATA;
	}

	for (unsigned int i = 0; i < 6; i++)
	{
		if(neighbors[i] != nullptr && neighbors[i]->state > DATA)
		{
			neighbors[i]->dispose(device);
			delete neighbors[i];
		}
	}
}

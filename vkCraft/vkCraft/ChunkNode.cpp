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

ChunkNode* ChunkNode::searchNode(glm::ivec3 index, std::vector<ChunkNode*> *nodes)
{
	if (std::find(nodes->begin(), nodes->end(), this) != nodes->end())
	{
		return nullptr;
	}

	nodes->push_back(this);

	for (unsigned int i = 0; i < 6; i++)
	{
		if (neighbors[i] != nullptr && neighbors[i]->index == index)
		{
			return neighbors[i];
		}
	}

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

void ChunkNode::searchNeighbors()
{
	std::vector<ChunkNode*> *nodes = new std::vector<ChunkNode*>();

	if (neighbors[ChunkNode::LEFT] == nullptr)
	{
		ChunkNode* left = searchNode({index.x - 1, index.y, index.z}, nodes);
		if (left != nullptr)
		{
			neighbors[ChunkNode::LEFT] = left;
		}	 
	}

	if (neighbors[ChunkNode::RIGHT] == nullptr)
	{
		nodes->clear();
		ChunkNode* right = searchNode({ index.x + 1, index.y, index.z }, nodes);
		if (right != nullptr)
		{
			neighbors[ChunkNode::RIGHT] = right;
		}
	}

	if (neighbors[ChunkNode::FRONT] == nullptr)
	{
		nodes->clear();
		ChunkNode* front = searchNode({ index.x, index.y, index.z - 1}, nodes);
		if (front != nullptr)
		{
			neighbors[ChunkNode::FRONT] = front;
		}
	}
	if (neighbors[ChunkNode::BACK] == nullptr)
	{
		nodes->clear();
		ChunkNode* back = searchNode({ index.x, index.y, index.z + 1}, nodes);
		if (back != nullptr)
		{
			neighbors[ChunkNode::BACK] = back;
		}
	}

	if (neighbors[ChunkNode::UP] == nullptr)
	{
		nodes->clear();
		ChunkNode* up = searchNode({ index.x, index.y + 1, index.z }, nodes);
		if (up != nullptr)
		{
			neighbors[ChunkNode::UP] = up;
		}
	}

	if (neighbors[ChunkNode::DOWN] == nullptr)
	{
		nodes->clear();
		ChunkNode* down = searchNode({ index.x, index.y - 1, index.z }, nodes);
		if (down != nullptr)
		{
			neighbors[ChunkNode::DOWN] = down;
		}
	}
	
	delete nodes;

	/*
	ChunkNode::fetchNeighborPath({ ChunkNode::RIGHT, ChunkNode::FRONT, ChunkNode::LEFT }, ChunkNode::FRONT);
	ChunkNode::fetchNeighborPath({ ChunkNode::RIGHT, ChunkNode::BACK, ChunkNode::LEFT }, ChunkNode::BACK);
	ChunkNode::fetchNeighborPath({ ChunkNode::RIGHT, ChunkNode::UP, ChunkNode::LEFT }, ChunkNode::UP);
	ChunkNode::fetchNeighborPath({ ChunkNode::RIGHT, ChunkNode::DOWN, ChunkNode::LEFT }, ChunkNode::DOWN);

	ChunkNode::fetchNeighborPath({ ChunkNode::LEFT, ChunkNode::FRONT, ChunkNode::RIGHT }, ChunkNode::FRONT);
	ChunkNode::fetchNeighborPath({ ChunkNode::LEFT, ChunkNode::BACK, ChunkNode::RIGHT }, ChunkNode::BACK);
	ChunkNode::fetchNeighborPath({ ChunkNode::LEFT, ChunkNode::UP, ChunkNode::RIGHT }, ChunkNode::UP);
	ChunkNode::fetchNeighborPath({ ChunkNode::LEFT, ChunkNode::DOWN, ChunkNode::RIGHT }, ChunkNode::DOWN);

	ChunkNode::fetchNeighborPath({ ChunkNode::FRONT, ChunkNode::LEFT, ChunkNode::BACK }, ChunkNode::LEFT);
	ChunkNode::fetchNeighborPath({ ChunkNode::FRONT, ChunkNode::RIGHT, ChunkNode::BACK }, ChunkNode::RIGHT);
	ChunkNode::fetchNeighborPath({ ChunkNode::FRONT, ChunkNode::UP, ChunkNode::BACK }, ChunkNode::UP);
	ChunkNode::fetchNeighborPath({ ChunkNode::FRONT, ChunkNode::DOWN, ChunkNode::BACK }, ChunkNode::DOWN);

	ChunkNode::fetchNeighborPath({ ChunkNode::BACK, ChunkNode::LEFT, ChunkNode::FRONT }, ChunkNode::LEFT);
	ChunkNode::fetchNeighborPath({ ChunkNode::BACK, ChunkNode::RIGHT, ChunkNode::FRONT }, ChunkNode::RIGHT);
	ChunkNode::fetchNeighborPath({ ChunkNode::BACK, ChunkNode::UP, ChunkNode::FRONT }, ChunkNode::UP);
	ChunkNode::fetchNeighborPath({ ChunkNode::BACK, ChunkNode::DOWN, ChunkNode::FRONT }, ChunkNode::DOWN);

	ChunkNode::fetchNeighborPath({ ChunkNode::UP, ChunkNode::LEFT, ChunkNode::DOWN }, ChunkNode::LEFT);
	ChunkNode::fetchNeighborPath({ ChunkNode::UP, ChunkNode::RIGHT, ChunkNode::DOWN }, ChunkNode::RIGHT);
	ChunkNode::fetchNeighborPath({ ChunkNode::UP, ChunkNode::FRONT, ChunkNode::DOWN }, ChunkNode::FRONT);
	ChunkNode::fetchNeighborPath({ ChunkNode::UP, ChunkNode::BACK, ChunkNode::DOWN }, ChunkNode::BACK);

	ChunkNode::fetchNeighborPath({ ChunkNode::DOWN, ChunkNode::LEFT, ChunkNode::UP }, ChunkNode::LEFT);
	ChunkNode::fetchNeighborPath({ ChunkNode::DOWN, ChunkNode::RIGHT, ChunkNode::UP }, ChunkNode::RIGHT);
	ChunkNode::fetchNeighborPath({ ChunkNode::DOWN, ChunkNode::FRONT, ChunkNode::UP }, ChunkNode::FRONT);
	ChunkNode::fetchNeighborPath({ ChunkNode::DOWN, ChunkNode::BACK, ChunkNode::UP }, ChunkNode::BACK);
	*/
}

void ChunkNode::fetchNeighborPath(std::array<int, 3> path, int position)
{
	if (neighbors[position] == nullptr)
	{
		ChunkNode *node = getNeighborPath(path);

		if (node != nullptr)
		{
			neighbors[position] = node;
		}
	}
	else
	{
		//std::cout << "VkCraft: fetchNeighborPath " << position << " already has a node stored." << std::endl;
	}

}

ChunkNode* ChunkNode::getNeighborPath(std::array<int, 3> path)
{
	//std::cout << "VkCraft: Path size is " << path.size() << "." << std::endl;

	if (path.size() < 1 || neighbors[path[0]] == nullptr)
	{
		//std::cout << "VkCraft: First node still does not exist." << std::endl;
		return nullptr;
	}

	ChunkNode* node = neighbors[path[0]];

	for (int i = 1; i < path.size(); i++)
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
	for (int i = 0; i < path.size(); i++)
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

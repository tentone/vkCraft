#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include <vector>

/**
 * Chunks store the world data.
 *
 * They are generated using a world generator and are organized into a chunk world.
 */
class Chunk
{
public:
	static const int SIZE = 32;

	static const int EMPTY = 0;
	static const int GRASS = 1;
	static const int SAND = 2;
	static const int STONE = 3;
	static const int DIRT = 4;
	static const int WATER = 4;

	/**
	 * Chunk data, constants defined in this class.
	 */
	int data[SIZE][SIZE][SIZE];

	/**
	 * Chunk position, in steps of one.
	 */
	glm::ivec3 position;

	/**
	 * Chunk constructor receives a position and creates chunk data based on it.
	 *
	 * The chunk position is organized in x,y,z, each step represents a move of CHUNK_SIZE in the world.
	 */
	Chunk(glm::ivec3 _position)
	{
		position = _position;
		generate();
	}

	/**
	 * Generate chunk data based on its position.
	 */
	void generate()
	{
		for (int x = 0; x < SIZE; x++)
		{
			for (int z = 0; z < SIZE; z++)
			{
				int v = x + position.x * SIZE;
				int w = z + position.z * SIZE;

				int height = cos(v / 25.0) * 5.0 + cos(w / 20.0 * sin(v / 10.0) * 2.0) * 3.0;

				for (int y = 0; y < SIZE; y++)
				{
					if (y < height)
					{
						data[x][y][z] = GRASS;
					}
					else
					{
						data[x][y][z] = EMPTY;
					}
				}
			}
		}
	}
};
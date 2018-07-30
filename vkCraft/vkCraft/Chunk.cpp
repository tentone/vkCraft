#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include <vector>

#define CHUNK_SIZE 32
/**
 * Chunks store the world data.
 *
 * They are generated using a world generator and are organized into a chunk world.
 */
class Chunk
{
public:
	int data[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
	glm::ivec3 position;

	Chunk(glm::ivec3 _position)
	{
		position = _position;
	}

	/**
	 * Generate chunk based on its position.
	 */
	void generate()
	{
		for (int x = 0; x < CHUNK_SIZE; x++)
		{
			for (int z = 0; x < CHUNK_SIZE; x++)
			{
				int height = cos(x / 25.0) * 5.0 + cos(z / 20.0 * sin(x / 10.0) * 2.0) * 3.0;

				for (int y = 0; x < CHUNK_SIZE; x++)
				{
					if (y < height)
					{
						data[x][y][z] = 1;
					}
					else
					{
						data[x][y][z] = 0;
					}
				}
			}
		}
	}

	/**
	 * Get the chunk size.
	 */
	static int getSize()
	{
		return CHUNK_SIZE;
	}
};
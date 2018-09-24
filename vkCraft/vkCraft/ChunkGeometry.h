#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include <vector>
#include <array>

#include "Geometry.cpp"
#include "Vertex.cpp"
#include "Chunk.h"

/**
 * Geometry to represent a chunk in the world.
 */
class ChunkGeometry : public Geometry
{
public:
	/**
	 * List of UV's for the blocks.
	 */
	const glm::vec4 BLOCK_UVS[8] =
	{
		calculateUV(12, 14, 16), //EMPTY
		calculateUV(0, 0, 16), //GRASS
		calculateUV(2, 1, 16), //SAND
		calculateUV(1, 0, 16), //STONE
		calculateUV(2, 0, 16), //DIRT
		calculateUV(15, 13, 16), //WATER
		calculateUV(15, 15, 16), //LAVA
		calculateUV(2, 4, 16) //CLOUD
	};

	/**
	* List of UV's for the fooliage.
	*/
	const glm::vec4 FLOOLIAGE_UVS[2] =
	{
		calculateUV(12, 0, 16), //FLOWER_RED
		calculateUV(13, 0, 16) //FLOWER_YELLOW
	};

	/**
	 * Calculate the UV for the element x, y in a grid with size.
	 */
	static glm::vec4 calculateUV(int x, int y, int size);

	/**
	 * Generate new geometry data for the attached chunk.
	 */
	void generate(Chunk *chunk);
};

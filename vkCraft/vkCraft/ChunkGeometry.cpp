#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include <vector>

#include "Geometry.cpp"
#include "BoxGeometry.cpp"
#include "Vertex.cpp"
#include "Chunk.cpp"

/**
 * Geometry to represent a chunk in the world.
 */
class ChunkGeometry : public Geometry
{
public:
	/**
	 * List of UV's for the materials.
	 */
	const std::vector<glm::vec4> UVS =
	{
		{0.0f, 0.0f, 1.0f, 1.0f}, //EMPTY
		{0.0f, 0.0f, 1/16.0f, 1/16.0f}, //GRASS
		{1/16.0f, 0.0f,1/8.0f, 1/16.0f} //SAND
	};

	/**
	 * Geometry for the cube voxel sides.
	 */
	const std::vector<glm::vec3> FRONT_VERTEX = { { -0.5f, -0.5f, 0.5f },{ 0.5f, -0.5f, 0.5f },{ 0.5f, 0.5f, 0.5f },{ -0.5f, 0.5f, 0.5f } };
	const glm::vec3 FRONT_NORMAL = { 0, 0, 1 };
	const std::vector<int> FRONT_INDEX = { 0, 2, 3, 0, 3, 1 };

	/**
	 * Chunk with the data to generate the geometry.
	 */
	Chunk *chunk;

	ChunkGeometry(Chunk *_chunk)
	{
		chunk = _chunk;
		generate();
	}

	/**
	 * Generate new geometry data for the attached chunk.
	 */
	void generate()
	{	
		vertices = {};
		indices = {};
		
		glm::ivec3 start = chunk->position;
		start *= Chunk::SIZE;
		
		glm::vec3 scale = glm::vec3(0.5, 0.5, 0.5);

		for (int x = 0; x < Chunk::SIZE; x++)
		{
			for (int z = 0; z < Chunk::SIZE; z++)
			{
				for (int y = 0; y < Chunk::SIZE; y++)
				{
					int value = chunk->data[x][y][z];

					if (value != Chunk::EMPTY)
					{
						//Transformation matrix
						glm::mat4 mat = glm::scale(glm::translate(glm::mat4(), glm::vec3(x + start.x, y + start.y, z + start.z)), scale);

						//Box geometry
						Geometry *geo = new BoxGeometry();
						geo->applyTransformationMatrix(mat);

						//Set the UV
						for (int i = 0; i < geo->vertices.size(); i += 4)
						{
							geo->vertices[i].uv.x = UVS[value].x;
							geo->vertices[i].uv.y = UVS[value].y;
							geo->vertices[i + 1].uv.x = UVS[value].z;
							geo->vertices[i + 1].uv.y = UVS[value].y;
							geo->vertices[i + 2].uv.x = UVS[value].x;
							geo->vertices[i + 2].uv.y = UVS[value].w;
							geo->vertices[i + 3].uv.x = UVS[value].z;
							geo->vertices[i + 3].uv.y = UVS[value].w;
						}

						this->merge(geo);
					}
				}
			}
		}
	}
};

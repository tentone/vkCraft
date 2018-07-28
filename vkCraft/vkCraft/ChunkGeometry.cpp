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

/**
 * Geometry to represent a chunk in the world.
 */
class ChunkGeometry : public Geometry
{
public:
	const std::vector<glm::vec4> UVS =
	{
		{0.0f, 0.0f, 0.25f, 0.25f}, //GROUND
		{0.25f, 0.0f, 0.50f, 0.25f} //GRASS
	};

	//Front
	const std::vector<glm::vec3> FRONT_VERTEX = { { -1, -1, 1 },{ 1, -1, 1 },{ 1, 1, 1 },{ -1, 1, 1 } };
	const glm::vec3 FRONT_NORMAL = { 0, 0, 1 };
	const std::vector<int> FRONT_INDEX = { 0, 2, 3, 0, 3, 1 };

	void generate()
	{
		vertices = {};
		indices = {};

		for (int x = 0; x < 32; x++)
		{
			for (int z = 0; z < 32; z++)
			{
				int y = floor(cos(x / 25.0) * 5.0 + cos(z / 20.0 * sin(x / 10.0) * 2.0) * 3.0);

				while (y >= -8)
				{
					glm::mat4 mat = glm::scale(glm::translate(glm::mat4(), glm::vec3(x, y, z)), glm::vec3(0.5, 0.5, 0.5));
					Geometry *geo = new BoxGeometry();
					geo->applyTransformationMatrix(mat);
					this->merge(geo);
					y--;
				}
			}
		}

		for (int i = 0; i < vertices.size(); i += 4)
		{
			int index = (i > (vertices.size() / 2)) ? 0 : 1;
			vertices[i].uv.x = UVS[index].x;
			vertices[i].uv.y = UVS[index].y;
			vertices[i + 1].uv.x = UVS[index].z;
			vertices[i + 1].uv.y = UVS[index].y;
			vertices[i + 2].uv.x = UVS[index].x;
			vertices[i + 2].uv.y = UVS[index].w;
			vertices[i + 3].uv.x = UVS[index].z;
			vertices[i + 3].uv.y = UVS[index].w;
		}
	}

};
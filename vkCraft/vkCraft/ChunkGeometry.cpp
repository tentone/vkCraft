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
	const glm::vec4 UV_GROUND = glm::vec4(0.0f, 0.0f, 0.25f, 0.25f);
	const glm::vec4 UV_GRASS = glm::vec4(0.25f, 0.0f, 0.50f, 0.25f);

	std::vector<glm::vec3> FRONT_FACE = {{-1, -1, 1}, {1, -1, 1}, {1, 1, 1},{-1, 1, 1 }};

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
			vertices[i].uv.x = UV_GRASS.x;
			vertices[i].uv.y = UV_GRASS.y;
			vertices[i + 1].uv.x = UV_GRASS.z;
			vertices[i + 1].uv.y = UV_GRASS.y;
			vertices[i + 2].uv.x = UV_GRASS.x;
			vertices[i + 2].uv.y = UV_GRASS.w;
			vertices[i + 3].uv.x = UV_GRASS.z;
			vertices[i + 3].uv.y = UV_GRASS.w;
		}
	}

};
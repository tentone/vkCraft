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
	//const glm::vec4 UV_GROUND = glm::vec4(0.0f, 0.0f, 0.25f, 0.25f);

	void generate()
	{
		vertices = {};
		indices = {};

		for (int x = 0; x < 128; x++)
		{
			for (int z = 0; z < 128; z++)
			{
				int y = floor(cos(x / 25.0) * 5.0 + cos(z / 20.0 * sin(x / 100.0) * 2.0) * 3.0);

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
	}

};
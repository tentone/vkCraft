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

		//BoxGeometry *geometry = new BoxGeometry();
		//geometry.applyTransformationMatrix(glm::translate(glm::mat4(), glm::vec3(x, floor(cos(x / 25) * 5 + cos(z / 20 * sin(x / 100) * 2) * 3), z)));
		//merge(geometry);
		/*for(int x = 0; x < 200; x++)
		{
			for(int z = 0; z < 200; z++)
			{
				BoxGeometry geometry;
				geometry.applyTransformationMatrix(glm::translate(glm::mat4(), glm::vec3(x, floor(cos(x / 25) * 5 + cos(z / 20 * sin(x / 100) * 2) * 3), z)));
				merge(&geometry);
			}
		}*/
	}

};
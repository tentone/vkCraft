#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>

#include "Geometry.cpp"
#include "Vertex.cpp"

/**
 * Geometry to represent a chunk in the world.
 */
class ChunkGeometry : public Geometry
{
public:
	const glm::vec4 UV_GROUND = glm::vec4(0.0f, 0.0f, 0.25f, 0.25f);

	void generate()
	{
		vertices = {};
		indices = {};
		
		/**
		for(var x = 0; x < 200; x++)
		{
		for(var z = 0; z < 200; z++)
		{
		var cube = new Mesh(geometry, material);
		cube.position.set(x, Math.floor(Math.cos(x / 25) * 5 + Math.cos(z / 20 * Math.sin(x / 100) * 2) * 3), z);
		scene.add(cube);
		}
		}
		 */

		for (unsigned int x = 0; x < 32; x++)
		{
			for (unsigned int y = 0; y < 32; y++)
			{
				//vertices.push_back();
				//vertices.push_back();
			}
		}	
	}

};
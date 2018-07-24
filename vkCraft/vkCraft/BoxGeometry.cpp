#pragma once

#include <vector>
#include "Geometry.cpp"
#include "Vertex.cpp"

class BoxGeometry : public Geometry
{
public:
	float width, height, depth;

	BoxGeometry(float _width = 1, float _height = 1, float _depth = 1)
	{
		width = _width;
		height = _height;
		depth = _depth;

		generate();
	}

	void generate()
	{
		vertices =
		{
			//Front face
			{ { -1, -1, 1 },{ 0, 0, 1 },{ 0, 0 } },
			{ { 1, -1, 1 },{ 0, 0, 1 },{ 1, 0 } },
			{ { 1, 1, 1 },{ 0, 0, 1 },{ 1, 1 } },
			{ { -1, 1, 1 },{ 0, 0, 1 },{ 0, 1 } },
			//Back face
			{ { -1, -1, -1 },{ 0, 0, -1 },{ 1, 0 } },
			{ { -1, 1, -1 },{ 0, 0, -1 },{ 1, 1 } },
			{ { 1, 1, -1 },{ 0, 0, -1 },{ 0, 1 } },
			{ { 1, -1, -1 },{ 0, 0, -1 },{ 0, 0 } },
			//Top face
			{ { -1, 1, -1 },{ 0, 1, 0 },{ 0, 1 } },
			{ { -1, 1, 1 },{ 0, 1, 0 },{ 0, 0 } },
			{ { 1, 1, 1 },{ 0, 1, 0 },{ 1, 0 } },
			{ { 1, 1, -1 },{ 0, 1, 0 },{ 1, 1 } },
			//Bottom face
			{ { -1, -1, -1 },{ 0, -1, 0 },{ 1, 1 } },
			{ { 1, -1, -1 },{ 0, -1, 0 },{ 0, 1 } },
			{ { 1, -1, 1 },{ 0, -1, 0 },{ 0, 0 } },
			{ { -1, -1, 1 },{ 0, -1, 0 },{ 1, 0 } },
			//Right face
			{ { 1, -1, -1 },{ 1, 0, 0 },{ 1, 0 } },
			{ { 1, 1, -1 },{ 1, 0, 0 },{ 1, 1 } },
			{ { 1, 1, 1 },{ 1, 0, 0 },{ 0, 1 } },
			{ { 1, -1, 1 },{ 1, 0, 0 },{ 0, 0 } },
			//Left face
			{ { -1, -1, -1 },{ -1, 0, 0 },{ 0, 0 } },
			{ { -1, -1, 1 },{ -1, 0, 0 },{ 1, 0 } },
			{ { -1, 1, 1 },{ -1, 0, 0 },{ 1, 1 } },
			{ { -1, 1, -1 },{ -1, 0, 0 },{ 0, 1 } }
		};

		for (int i = 0; i < vertices.size(); i++)
		{
			vertices[i].pos.x *= width;
			vertices[i].pos.y *= depth;
			vertices[i].pos.z *= depth;
		}

		indices =
		{
			//Front face
			0, 1, 2, 0, 2, 3,
			//Back face
			4, 5, 6, 4, 6, 7,
			//Top face
			8, 9, 10, 8, 10, 11,
			//Bottom face
			12, 13, 14, 12, 14, 15,
			//Right face
			16, 17, 18, 16, 18, 19,
			//Left face
			20, 21, 22, 20, 22, 23
		};
	}
};
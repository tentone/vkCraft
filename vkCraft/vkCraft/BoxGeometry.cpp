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
			{ { -1, -1, 1 },{ 0, 0, 1 },{ 0, 0 } }, //0
			{ { -1, 1, 1 },{ 0, 0, 1 },{ 0, 1 } }, //3
			{ { 1, -1, 1 },{ 0, 0, 1 },{ 1, 0 } }, //1
			{ { 1, 1, 1 },{ 0, 0, 1 },{ 1, 1 } }, //2

			//Back face
			{ { 1, -1, -1 },{ 0, 0, -1 },{ 0, 0 } }, //7
			{ { 1, 1, -1 },{ 0, 0, -1 },{ 0, 1 } }, //6
			{ { -1, -1, -1 },{ 0, 0, -1 },{ 1, 0 } }, //4
			{ { -1, 1, -1 },{ 0, 0, -1 },{ 1, 1 } }, //5
			
			//Top face
			{ { -1, 1, 1 },{ 0, 1, 0 },{ 0, 0 } }, //9
			{ { -1, 1, -1 },{ 0, 1, 0 },{ 0, 1 } }, //8
			{ { 1, 1, 1 },{ 0, 1, 0 },{ 1, 0 } }, //10
			{ { 1, 1, -1 },{ 0, 1, 0 },{ 1, 1 } }, //11

			//Bottom face
			{ { 1, -1, 1 },{ 0, -1, 0 },{ 0, 0 } }, //14
			{ { 1, -1, -1 },{ 0, -1, 0 },{ 0, 1 } }, //13
			{ { -1, -1, 1 },{ 0, -1, 0 },{ 1, 0 } }, //15
			{ { -1, -1, -1 },{ 0, -1, 0 },{ 1, 1 } }, //12

			//Right face
			{ { 1, -1, 1 },{ 1, 0, 0 },{ 0, 0 } }, //19
			{ { 1, 1, 1 },{ 1, 0, 0 },{ 0, 1 } }, //18
			{ { 1, -1, -1 },{ 1, 0, 0 },{ 1, 0 } }, //16
			{ { 1, 1, -1 },{ 1, 0, 0 },{ 1, 1 } }, //17

			//Left face
			{ { -1, -1, -1 },{ -1, 0, 0 },{ 0, 0 } }, //20
			{ { -1, 1, -1 },{ -1, 0, 0 },{ 0, 1 } }, //23
			{ { -1, -1, 1 },{ -1, 0, 0 },{ 1, 0 } }, //21
			{ { -1, 1, 1 },{ -1, 0, 0 },{ 1, 1 } } //22
		};

		indices =
		{
			//Front face
			0, 2, 3, 0, 3, 1,

			//Back face
			6, 7, 5, 6, 5, 4,

			//Top face
			9, 8, 10, 9, 10, 11,

			//Bottom face
			15, 13, 12, 15, 12, 14,

			//Right face
			18, 19, 17, 18, 17, 16,

			//Left face
			20, 22, 23, 20, 23, 21
		};

		for (int i = 0; i < vertices.size(); i++)
		{
			vertices[i].pos.x *= width;
			vertices[i].pos.y *= depth;
			vertices[i].pos.z *= depth;
		}
	}
};
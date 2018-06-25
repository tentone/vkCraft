#pragma once

#include <vector>
#include "Geometry.cpp"
#include "Vertex.cpp"

class BoxGeometry : public Geometry
{
public:
	int width, height, depth;
	int widthSegments, heightSegments, depthSegments;

	BoxGeometry(int _width = 1, int _height = 1, int _depth = 1, int _widthSegments = 1, int _heightSegments = 1, int _depthSegments = 1)
	{
		width = _width;
		height = _height;
		depth = _depth;
		widthSegments = _widthSegments;
		heightSegments = _heightSegments;
		depthSegments = _depthSegments;
	}

	void generate()
	{
		vertices =
		{
			{ { -0.5f, -0.5f, 0.0f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
			{ { 0.5f, -0.5f, 0.0f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
			{ { 0.5f, 0.5f, 0.0f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } }
		};

		indices =
		{
			0, 1, 2
		};
	}
};
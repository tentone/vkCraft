#pragma once

#include <vector>
#include "Geometry.h"
#include "Vertex.h"

class BoxGeometry : public Geometry
{
public:
	float width, height, depth;

	BoxGeometry(float _width = 1, float _height = 1, float _depth = 1);

	void generate();
};
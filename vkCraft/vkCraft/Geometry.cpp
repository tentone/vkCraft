#pragma once

#include <vector>
#include "Vertex.cpp"

class Geometry
{
public:
	std::vector<Vertex> vertices;
	std::vector<uint16_t> indices;
};
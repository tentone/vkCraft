#pragma once

#include "ChunkGeometry.h"

glm::vec4 ChunkGeometry::calculateUV(int x, int y, int size)
{
	float step = 1.0 / size;
	return glm::vec4(step * x, step * y, step * x + step, step * y + step);
}

void ChunkGeometry::generate(Chunk *chunk)
{	
	vertices.clear();
	indices.clear();
		
	int size = 0;
	glm::ivec3 start = chunk->index;
	start *= Chunk::SIZE;

	for (int x = 0; x < Chunk::SIZE; x++)
	{
		for (int z = 0; z < Chunk::SIZE; z++)
		{
			for (int y = 0; y < Chunk::SIZE; y++)
			{
				int value = chunk->data[x][y][z];

				if (value != Chunk::EMPTY)
				{
					//Base
					float ix = x + start.x;
					float iy = y + start.y;
					float iz = z + start.z;
						
					//Positive
					float px = 0.5f + ix;
					float py = 0.5f + iy;
					float pz = 0.5f + iz;
						
					//Negative
					float nx = ix - 0.5f;
					float ny = iy - 0.5f;
					float nz = iz - 0.5f;

					//Top face
					if (y == Chunk::SIZE - 1 || chunk->data[x][y + 1][z] == Chunk::EMPTY)
					{
						indices.push_back(size + 1);
						indices.push_back(size);
						indices.push_back(size + 2);
						indices.push_back(size + 1);
						indices.push_back(size + 2);
						indices.push_back(size + 3);

						vertices.push_back({ { nx, py, pz },{ 0, 1, 0 },{ BLOCK_UVS[value].x, BLOCK_UVS[value].y } });
						vertices.push_back({ { nx, py, nz },{ 0, 1, 0 },{ BLOCK_UVS[value].z, BLOCK_UVS[value].y } });
						vertices.push_back({ { px, py, pz },{ 0, 1, 0 },{ BLOCK_UVS[value].x, BLOCK_UVS[value].w } });
						vertices.push_back({ { px, py, nz },{ 0, 1, 0 },{ BLOCK_UVS[value].z, BLOCK_UVS[value].w } });
						size += 4;
					}

					//Bottom face
					if (y == 0 || chunk->data[x][y - 1][z] == Chunk::EMPTY)
					{
						indices.push_back(size + 3);
						indices.push_back(size + 1);
						indices.push_back(size);
						indices.push_back(size + 3);
						indices.push_back(size);
						indices.push_back(size + 2);

						vertices.push_back({ { px, ny, pz },{ 0, -1, 0 },{ BLOCK_UVS[value].x, BLOCK_UVS[value].y } });
						vertices.push_back({ { px, ny, nz },{ 0, -1, 0 },{ BLOCK_UVS[value].z, BLOCK_UVS[value].y } });
						vertices.push_back({ { nx, ny, pz },{ 0, -1, 0 },{ BLOCK_UVS[value].x, BLOCK_UVS[value].w } });
						vertices.push_back({ { nx, ny, nz },{ 0, -1, 0 },{ BLOCK_UVS[value].z, BLOCK_UVS[value].w } });
						size += 4;
					}

					//Front face
					if (z == Chunk::SIZE - 1 || chunk->data[x][y][z + 1] == Chunk::EMPTY)
					{
						indices.push_back(size);
						indices.push_back(size + 2);
						indices.push_back(size + 3);
						indices.push_back(size);
						indices.push_back(size + 3);
						indices.push_back(size + 1);

						vertices.push_back({ { nx, ny, pz },{ 0, 0, 1 },{ BLOCK_UVS[value].x, BLOCK_UVS[value].y } });
						vertices.push_back({ { nx, py, pz },{ 0, 0, 1 },{ BLOCK_UVS[value].z, BLOCK_UVS[value].y } });
						vertices.push_back({ { px, ny, pz },{ 0, 0, 1 },{ BLOCK_UVS[value].x, BLOCK_UVS[value].w } });
						vertices.push_back({ { px, py, pz },{ 0, 0, 1 },{ BLOCK_UVS[value].z, BLOCK_UVS[value].w } });
						size += 4;
					}

					//Back face
					if (z == 0 || chunk->data[x][y][z - 1] == Chunk::EMPTY)
					{
						indices.push_back(size + 2);
						indices.push_back(size + 3);
						indices.push_back(size + 1);
						indices.push_back(size + 2);
						indices.push_back(size + 1);
						indices.push_back(size);

						vertices.push_back({ { px, ny, nz },{ 0, 0, -1 },{ BLOCK_UVS[value].x, BLOCK_UVS[value].y } });
						vertices.push_back({ { px, py, nz },{ 0, 0, -1 },{ BLOCK_UVS[value].z, BLOCK_UVS[value].y } });
						vertices.push_back({ { nx, ny, nz },{ 0, 0, -1 },{ BLOCK_UVS[value].x, BLOCK_UVS[value].w } });
						vertices.push_back({ { nx, py, nz },{ 0, 0, -1 },{ BLOCK_UVS[value].z, BLOCK_UVS[value].w } });
						size += 4;
					}

					//Right face
					if (x == Chunk::SIZE - 1 || chunk->data[x + 1][y][z] == Chunk::EMPTY)
					{
						indices.push_back(size + 2);
						indices.push_back(size + 3);
						indices.push_back(size + 1);
						indices.push_back(size + 2);
						indices.push_back(size + 1);
						indices.push_back(size);

						vertices.push_back({ { px, ny, pz },{ 1, 0, 0 },{ BLOCK_UVS[value].x, BLOCK_UVS[value].y } });
						vertices.push_back({ { px, py, pz },{ 1, 0, 0 },{ BLOCK_UVS[value].z, BLOCK_UVS[value].y } });
						vertices.push_back({ { px, ny, nz },{ 1, 0, 0 },{ BLOCK_UVS[value].x, BLOCK_UVS[value].w } });
						vertices.push_back({ { px, py, nz },{ 1, 0, 0 },{ BLOCK_UVS[value].z, BLOCK_UVS[value].w } });
						size += 4;
					}

					//Left face
					if (x == 0 || chunk->data[x - 1][y][z] == Chunk::EMPTY)
					{
						indices.push_back(size);
						indices.push_back(size + 2);
						indices.push_back(size + 3);
						indices.push_back(size);
						indices.push_back(size + 3);
						indices.push_back(size + 1);

						vertices.push_back({ { nx, ny, nz },{ -1, 0, 0 },{ BLOCK_UVS[value].x, BLOCK_UVS[value].y } });
						vertices.push_back({ { nx, py, nz },{ -1, 0, 0 },{ BLOCK_UVS[value].z, BLOCK_UVS[value].y } });
						vertices.push_back({ { nx, ny, pz },{ -1, 0, 0 },{ BLOCK_UVS[value].x, BLOCK_UVS[value].w } });
						vertices.push_back({ { nx, py, pz },{ -1, 0, 0 },{ BLOCK_UVS[value].z, BLOCK_UVS[value].w } });
						size += 4;
					}
				}
			}
		}
	}
}

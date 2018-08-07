#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include <vector>

/**
 * Chunks store the world data.
 *
 * They are generated using a world generator and are organized into a chunk world.
 */
class Chunk
{
public:
	static const int SIZE = 16;
	static const int WATER_LEVEL = 0;
	static const int CLOUD_LEVEL = SIZE * 2;

	static const int EMPTY = 0;

	//Block
	static const int GRASS = 1;
	static const int SAND = 2;
	static const int STONE = 3;
	static const int DIRT = 4;
	static const int WATER = 5;
	static const int LAVA = 6;
	static const int CLOUDS = 7;
	
	//Fooliage
	static const int FLOWER_RED = 500;
	static const int FLOWER_YELLOW = 501;
	static const int BIRCH = 502;

	/**
	 * Chunk data, constants defined in this class.
	 */
	int data[SIZE][SIZE][SIZE];

	/**
	 * Chunk position, in steps of one.
	 */
	glm::ivec3 position;

	/**
	 * Chunk constructor receives a position and creates chunk data based on it.
	 *
	 * The chunk position is organized in x,y,z, each step represents a move of CHUNK_SIZE in the world.
	 */
	Chunk(glm::ivec3 _position)
	{
		position = _position;
		generate();
	}

	/**
	 * Get world position of a block, inside of this chunk.
	 */
	glm::vec3 getWorldPosition(int x, int y, int z)
	{
		return glm::vec3(position.x * SIZE + x, position.y * SIZE + y, position.z * SIZE + z);
	}

	/**
	 * Generate chunk data based on its position.
	 */
	void generate()
	{
		int seed = 782364;

		for (int x = 0; x < SIZE; x++)
		{
			for (int z = 0; z < SIZE; z++)
			{
				int v = x + position.x * SIZE;
				int w = z + position.z * SIZE;
				int noise = getHeight(v, w, seed);

				for (int y = 0; y < SIZE; y++)
				{
					int h = y + position.y * SIZE;
					data[x][y][z] = getBlock(h, noise);
				}
			}
		}
		/*

		*/

		/*
		for (int x = 0; x < SIZE; x++)
		{
			for (int z = 0; z < SIZE; z++)
			{
				int v = x + position.x * SIZE;
				int w = z + position.z * SIZE;

				int height = sin((v + w) / 50.0) * cos(v / 300.0) * 7.0 + cos(w / 20.0 * sin(v / 10.0) * 2.0) * 10.0;

				for (int y = 0; y < SIZE; y++)
				{
					int h = y + position.y * SIZE;

					if (h < height)
					{
						data[x][y][z] = GRASS;
					}
					else
					{
						data[x][y][z] = EMPTY;
					}
				}
			}
		}

		for (int x = 0; x < SIZE; x++)
		{
			for (int z = 0; z < SIZE; z++)
			{
				int last = data[x][0][z];

				for (int y = 0; y < SIZE; y++)
				{
					if (last != data[x][y][z])
					{
						data[x][y][z] = SAND;
						break;
					}

					last = data[x][y][z];
				}
			}
		}
		*/
	}

	//Perlin noise generator
	double findNoise(double x, double y, int seed)
	{
		int n = (int)x + (int)y * 57;
		n += seed;
		n = (n << 13) ^ n;

		unsigned int nn = (n * (n * n * 60493 + 19990303) + 1376312589);
		
		return 1.0 - ((double)nn / 1073741824.0);
	}

	double interpolate(double a, double b, double x)
	{
		double ft = x * 3.1415927;
		double f = (1.0 - cos(ft)) * 0.5;
		return a * (1.0 - f) + b * f;
	}

	double getNoise(double x, double y, int seed)
	{
		double floorx = (double)((int)x);
		double floory = (double)((int)y);

		//Integer declaration
		double s, t, u, v;

		//Get the surrounding pixels to calculate the transition.
		s = findNoise(floorx, floory, seed);
		t = findNoise(floorx + 1, floory, seed);
		u = findNoise(floorx, floory + 1, seed);
		v = findNoise(floorx + 1, floory + 1, seed);

		//Interpolate between the values.
		double int1 = interpolate(s, t, x - floorx);

		//Use x-floorx, to get 1st dimension, it's part of the cosine formula.
		double int2 = interpolate(u, v, x - floorx);

		//Use y-floory, to get the 2nd dimension.
		return interpolate(int1, int2, y - floory);
	}

	/**
	 * Here we get how terrain at X, Y is high. zoomget is only for some testing reasons.
	 * Here you can edit maximum and minimum level of height.
	 * Also here you pass seed. It's int.
	 */
	int getHeight(int x, int y, int seed, double zoomget = 150)
	{
		double frequencyPower = 2.0;
		double amplitudePower = 0.5;

		double zoom = zoomget;
		double noise = 0;

		int octaves = 6;

		//Loop trough the octaves
		for (int a = 0; a < octaves - 1; a++)
		{
			//Increase the frequency with every loop of the octave.
			double frequency = pow(frequencyPower, a);

			//Decrese the amplitude with every loop of the octave.
			double amplitude = pow(amplitudePower, a);

			//Perlin noise functions. It calculates all our zoom and frequency and amplitude
			noise += getNoise(((double)x) * frequency / zoom, ((double)y) / zoom * frequency, seed) * amplitude;
		}

		double maxHeight = SIZE * 4;
		double minHeight = 0;

		return (int)(((noise + 1) / 2.0) * (maxHeight - minHeight));
	}

	/** 
	 * Here we get what kind of block it is.
	 * z is which block we are currently in column.
	 * height is height of block at this collumn.
	 */
	int getBlock(int z, int height)
	{
		if (z > WATER_LEVEL)
		{
			if (z > height) { return EMPTY; }
			if (z == height) { return GRASS; }
			if (z > height - 7) { return DIRT; }
		}
		else
		{
			if ((z > height + 5)) { return WATER; }
			if ((z > height - 5)) { return SAND; }
			if ((z > height - 10)) { return DIRT; }
		}

		return STONE;
	}
};
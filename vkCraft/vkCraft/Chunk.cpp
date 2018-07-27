#pragma once

/**
 * Chunks store the world data.
 *
 * They are generated using a world generator and are organized into a chunk world.
 */
class Chunk
{
public:
	int data[32][32][32];

	Chunk()
	{
		
	}
};
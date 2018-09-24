#pragma once

#ifndef TG_H
#define TG_H

#include "SimplexNoise.h"
#include "Interpolation.h"
#include "ChunkManager.h"

namespace voxelEngine {

	class Voxel;
	class Chunk;

	enum class ChunkType
	{
		ChunkType_Default = 0,

		ChunkType_Grass,
		ChunkType_Oak_Forest,
		ChunkType_Hill,
	};

	class TerrainGenerator {

	public:
		TerrainGenerator(int seed);
		TerrainGenerator();
		~TerrainGenerator();

		voxelEngine::Voxel GetVoxelValue(int x, int y, int z, int chunkX, int chunkZ);
		double GetHeight(int x, int z);
		int GetVoxelTerrainType(int x, int y, int z);

	private:
		int m_seed;
		const int smoothValue = 4;
	};

}

#endif
#pragma once
#include "SimplexNoise.h"
#include "Interpolation.h"
#include "Chunk.h"

namespace voxelEngine {

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
		~TerrainGenerator();

		voxelEngine::Voxel GetVoxelValue(int x, int y, int z, int chunkX, int chunkZ);
		double GetHeight(int x, int z);
		int GetVoxelTerrainType(int x, int y, int z);

	private:
		int m_seed;
	};

}
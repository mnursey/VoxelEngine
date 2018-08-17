#include "TerrainGenerator.h"

voxelEngine::TerrainGenerator::TerrainGenerator(int seed)
	:m_seed(seed)
{

}

voxelEngine::TerrainGenerator::~TerrainGenerator()
{

}

voxelEngine::Voxel voxelEngine::TerrainGenerator::GetVoxelValue(int x, int y, int z, int chunkX, int chunkZ)
{
	// Get Chunk Type
	int chunkType = GetVoxelTerrainType(x, y ,z);

	double height = 0;

	voxelEngine::BlockType bt;
	if (chunkType == (int)ChunkType::ChunkType_Grass)
	{
		height = GetHeight(x, z);
		bt = BlockType_Grass;
	}

	if (chunkType == (int)ChunkType::ChunkType_Hill)
	{
		height = GetHeight(x, z);
		bt = BlockType_Stone;
	}

	if ((int)height < 1)
		height = 1.0;

	//GENERATE VOXELS
	if (y > (int)height)
		bt = voxelEngine::BlockType_Air;


	return voxelEngine::Voxel(bt, x, y, z,   height / 100 - 0.06 - ((int)height % 4) * 0.02);
}

double voxelEngine::TerrainGenerator::GetHeight(int x, int z)
{
	double nX = 1.0;
	double nZ = 1.0;
	if (x < 0)
		nX = -1.0;
	if (z < 0)
		nZ = -1.0;

	int chunkType = GetVoxelTerrainType(x, 1, z);
	
	int smoothValue = 4;

	double height = 1.0;
	double amplitude[3];
	double frequency[3];
	double multiplier = 1.0;
	double min = 1.0;


	if (x % smoothValue == 0 && z % smoothValue == 0)
	{
		if (chunkType == (int)ChunkType::ChunkType_Grass)
		{
			frequency[0] = 60.0; frequency[1] = 20.0; frequency[2] = 5.0;
			amplitude[0] = 1.0; amplitude[1] = 0.05; amplitude[2] = 0.016;
			multiplier = 6.0;
			min = 6.0;
		}

		if (chunkType == (int)ChunkType::ChunkType_Hill)
		{
			frequency[0] = 100.0; frequency[1] = 10.0; frequency[2] = 5.0;
			amplitude[0] = 1.0; amplitude[1] = 0.1; amplitude[2] = 0.05;
			multiplier = 20.0;
			min = 20.0;
		}

		height = ((amplitude[0]) * SimplexNoise::noise(x / frequency[0], z / frequency[0])) + (amplitude[1]) * (SimplexNoise::noise(x / frequency[1], z / frequency[1])) + (amplitude[2]) * (SimplexNoise::noise(x / frequency[2], z / frequency[2]));
		height /= (amplitude[0] + amplitude[1] + amplitude[2]);
		height *= multiplier;
		height += min;

		return height;
	}
	else
	{
		double northSouth[2] = { (z / smoothValue) * smoothValue + (smoothValue * nZ) , (z / smoothValue) * smoothValue };
		double eastWest[2] = { (x / smoothValue) * smoothValue + (smoothValue * nX), (x / smoothValue) * smoothValue };

		double xP = (x % smoothValue) / (smoothValue * 1.0) * nX;
		double zP = (z % smoothValue) / (smoothValue * 1.0) * nZ;

		height = binterpolate(GetHeight(eastWest[1], northSouth[0]), GetHeight(eastWest[0], northSouth[0]), GetHeight(eastWest[1], northSouth[1]), GetHeight(eastWest[0], northSouth[1]), xP, zP);
		return height;
	}
}

int voxelEngine::TerrainGenerator::GetVoxelTerrainType(int x, int y, int z)
{
	double amplitude[3];
	double frequency[3];

	frequency[0] = 40.0; frequency[1] = 20.0; frequency[2] = 5.0;
	amplitude[0] = 1.0; amplitude[1] = 20.0; amplitude[2] = 60.0;

	double value = ((1.0 / amplitude[0]) * SimplexNoise::noise(x / frequency[0], z / frequency[0])) + (1.0 / amplitude[1]) * (SimplexNoise::noise(x / frequency[1], z / frequency[1])) + (1.0 / amplitude[2]) * (SimplexNoise::noise(x / frequency[2], z / frequency[2]));
	int type = (int)ChunkType::ChunkType_Default;

	if (value < 0.5)
		type = (int)ChunkType::ChunkType_Grass;
	else
		type = (int)ChunkType::ChunkType_Hill;

	return type;
}
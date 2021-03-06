#pragma once

namespace voxelEngine {

	static float VOXEL_POSITIONS[6 * 6 * 6] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	static unsigned int VOXEL_INDICIES[6 * 6] = {
		0, 1, 2,
		0, 2, 3,

		4, 5, 6,
		4, 6, 7,

		8, 9, 10,
		8, 10, 11,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		20, 21, 22,
		20, 22, 23
	};

	static float VOXEL_POSITIONS_I[6 * 6 * 4] = {
		-0.5f, -0.5f, -0.5f,		  0.0f,	0.0f, -1.0f, // 0
		0.5f, -0.5f, -0.5f,			 0.0f,	0.0f, -1.0f,  // 1
		0.5f,  0.5f, -0.5f,			 0.0f,	0.0f, -1.0f,  // 2
		-0.5f,  0.5f, -0.5f,		  0.0f,	 0.0f, -1.0f, // 3

		-0.5f, -0.5f,  0.5f,		  0.0f,	 0.0f, 1.0f,  // 4
		0.5f, -0.5f,  0.5f,			 0.0f,	0.0f, 1.0f,   // 5
		0.5f,  0.5f,  0.5f,			 0.0f,	0.0f, 1.0f,   // 6
		-0.5f,  0.5f,  0.5f,		  0.0f,	 0.0f, 1.0f,  // 7

		-0.5f,  0.5f,  0.5f,		 -1.0f,	 0.0f,  0.0f, // 8
		-0.5f,  0.5f, -0.5f,		 -1.0f,	 0.0f,  0.0f, // 9
		-0.5f, -0.5f, -0.5f,		 -1.0f,	 0.0f,  0.0f, // 10
		-0.5f, -0.5f,  0.5f,		 -1.0f,	 0.0f,  0.0f, // 11

		0.5f,  0.5f, -0.5f,			 1.0f,	0.0f,  0.0f,  // 12
		0.5f, -0.5f, -0.5f,			 1.0f,	0.0f,  0.0f,  // 13
		0.5f, -0.5f,  0.5f,			 1.0f,	0.0f,  0.0f,  // 14
		0.5f,  0.5f,  0.5f,			 1.0f,	0.0f,  0.0f,  // 15

		-0.5f, -0.5f, -0.5f,		  0.0f,	-1.0f,  0.0f, // 16
		0.5f, -0.5f, -0.5f,			 0.0f, -1.0f,  0.0f,  // 17
		0.5f, -0.5f,  0.5f,			 0.0f, -1.0f,  0.0f,  // 18
		-0.5f, -0.5f,  0.5f,		  0.0f,	-1.0f,  0.0f, // 19

		-0.5f,  0.5f, -0.5f,		  0.0f,	 1.0f,  0.0f, // 20
		0.5f,  0.5f, -0.5f,			 0.0f,	1.0f,  0.0f,  // 21
		0.5f,  0.5f,  0.5f,			 0.0f,	1.0f,  0.0f,  // 22
		-0.5f,  0.5f,  0.5f,		  0.0f,	 1.0f,  0.0f, // 23
	};

	enum BlockType
	{
		BlockType_Air = 0,

		BlockType_Grass,
		BlockType_Dirt,
		BlockType_Stone,
		BlockType_Wood,
	};

	static const float Block_Colors[5][4] = {
		{1.0f, 1.0f, 1.0f, 0.0f},										// AIR
		{ 96.0f / 255.0f, 128.0f / 255.0f, 56.0f / 255.0f, 1.0f },		// GRASS
		{ 78.0f / 255.0f, 52.0f / 255.0f, 46.0f / 255.0f, 1.0f },		// DIRT
		{ 66.0f / 255.0f, 66.0f / 255.0f, 66.0f / 255.0f, 1.0f },		// STONE
		{ 61.0f / 255.0f, 153.0f / 255.0f, 112.0f / 255.0f, 1.0f }		// WOOD
	};

	class Voxel {
	public:
		Voxel();
		Voxel(BlockType, int, int, int, float);
		~Voxel();
		
		void GetPosition(int* x, int* y, int* z);
		int GetVoxelType();
		static const int s_VOXEL_SIZE = 1;
		float m_moisture;

	private:
		int m_x, m_y, m_z;
		BlockType  m_blockType;
	};
}
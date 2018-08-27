#pragma once

#include "Voxel.h"
#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include "time.h"
#include "RenderObject.h"
#include "VertexBufferLayout.h"
#include "TerrainGenerator.h"

namespace voxelEngine {

	class Chunk {
	public:
		static const int s_SIZE = 16;
		static const int s_HEIGHT = 64;

	private:
		int m_seed;

		int m_bpf;
		int m_currentX = 0;
		int m_currentY = 0;
		int m_currentZ = 0;

		Voxel m_pVoxels[s_SIZE][s_HEIGHT][s_SIZE];
		void ActiveNeighbours(int x, int y, int z, bool* values);
		void GenerateRenderData();

	public:

		Chunk(int, int, int, int);
		Chunk(int, int, int, int, int);

		~Chunk();

		int Build();
		bool built = false;
		void GetPosition(int* position);
		void Update(float delta);
		int m_x, m_y, m_z;
		RenderObject* renderObject;
	};
}
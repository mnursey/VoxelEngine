#pragma once

#ifndef CHUNK_H
#define CHUNK_H

#include "Voxel.h"
#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include "time.h"
#include "RenderObject.h"
#include "VertexBufferLayout.h"
#include "ChunkManager.h"

namespace voxelEngine {

	class TerrainGenerator;

	class Chunk {
	public:
		static const int s_SIZE = 16;
		static const int s_HEIGHT = 16;

	private:
		int m_seed;

		int m_bpf;
		int m_currentX = 0;
		int m_currentY = 0;
		int m_currentZ = 0;

		TerrainGenerator* tGen;

		Voxel m_pVoxels[s_SIZE][s_HEIGHT][s_SIZE];
		void ActiveNeighbours(int x, int y, int z, bool* values);

	public:

		Chunk(int, int, int, int);
		Chunk(int, int, int, int, int);

		~Chunk();

		int Build();
		void BuildComplete();
		bool built = false;
		void GenerateRenderData();
		void GetPosition(int* position);
		void Update(float delta);
		int m_x, m_y, m_z;
		RenderObject* renderObject;
	};
}

#endif
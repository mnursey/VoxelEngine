#pragma once
#include <vector>
#include "Chunk.h"

namespace voxelEngine {

	class ChunkManager {

	private:
		int seed = 47;
		int m_VoxelPosition[3];
		static const int m_viewDistance = 10;
		static const int m_VoxelsLoadedPerFrame = 1024;

		void LoadChunk(int x, int y, int z);
		void UnLoadChunk(int activeChunkIndex);
		void SaveChunk(int x, int y, int z);


	public:
		void WordToVoxelPosition(float worldPos[], int* voxelPos);
		void Update(float viewPosition[]);
		void UpdateLoadQueue();
		std::vector<Chunk*> activeChunks;
		std::vector<Chunk*> loadQueue;
		ChunkManager();
		~ChunkManager();
	};
}
#pragma once
#include <vector>
#include <map>
#include <unordered_map>
#include "Chunk.h"
#include <array>

namespace voxelEngine {

	class ChunkManager {

	private:
		int seed = 47;
		int m_VoxelPosition[3];
		static const int m_viewDistance = 10;
		static const int m_VoxelsLoadedPerFrame = 1024;

		int m_prevCameraPosition[3] = { 0,0,0 };

		void LoadChunk(int x, int y, int z);
		void UnLoadChunk(int x, int z);
		void SaveChunk(int x, int y, int z);

		std::vector<Chunk*> queueChunks;

		std::unordered_map<std::string, Chunk*> managedChunks;
		bool firstRun = true;

	public:
		void WordToVoxelPosition(float worldPos[], int* voxelPos);
		void Update(float viewPosition[]);
		void UpdateLoadQueue(int cameraChunkPosition[]);
		std::vector<Chunk*> activeChunks;

		ChunkManager();
		~ChunkManager();
	};
}
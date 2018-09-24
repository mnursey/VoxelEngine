#pragma once
#include <vector>
#include <map>
#include <unordered_map>
#include "Chunk.h"
#include "TerrainGenerator.h"
#include <array>
#include <future>
#include <mutex>
#include <atomic>

enum class ThreadState
{
	Idle = 0,
	Working = 1,
	Done = 2
};

namespace voxelEngine {

	class ChunkManager {

	private:
		const static int worldHeight = 3;
		const static int threadCount = 4;
		int seed = 47;
		int m_VoxelPosition[3];
		static const int m_viewDistance = 16;
		static const int m_VoxelsLoadedPerFrame = 1024;

		int m_prevCameraPosition[3] = { 0,0,0 };

		void LoadChunk(int x, int y, int z);
		void UnLoadChunk(int x, int y, int z);
		void SaveChunk(int x, int y, int z);

		std::vector<Chunk*> queueChunks;

		std::unordered_map<std::string, Chunk*> managedChunks;
		bool firstRun = true;

		std::future<Chunk*> threads[threadCount];
		// Check if valid
		std::array<std::atomic<int>, threadCount> threadStatus;
		int numberOfUnusedThreads = threadCount;

	public:
		void WordToVoxelPosition(float worldPos[], int* voxelPos);
		void Update(float viewPosition[]);
		static voxelEngine::Chunk* LoadWorker(Chunk* chunk, std::atomic<int>* state);
		void UpdateLoadQueue(int cameraChunkPosition[]);
		std::vector<Chunk*> activeChunks;

		ChunkManager();
		~ChunkManager();
	};
}
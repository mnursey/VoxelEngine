#include "ChunkManager.h"

void voxelEngine::ChunkManager::LoadChunk(int x, int y, int z)
{
	Chunk* newChunk = new Chunk(x, y ,z, seed, m_VoxelsLoadedPerFrame);
	loadQueue.push_back(newChunk);
	//std::cout << "Loading Chunk " << x << ":" << y << ":"<< z << std::endl;
}

void voxelEngine::ChunkManager::UnLoadChunk(int activeChunkIndex)
{
	Chunk* temp = activeChunks[activeChunkIndex];
	activeChunks.erase(activeChunks.begin() + activeChunkIndex);
	delete temp;
}

void voxelEngine::ChunkManager::SaveChunk(int x, int y, int z)
{

}

void voxelEngine::ChunkManager::WordToVoxelPosition(float worldPos[], int* voxelPos)
{
	voxelPos[0] = round(worldPos[0]);
	voxelPos[1] = round(worldPos[1]);
	voxelPos[2] = round(worldPos[2]);
}

void voxelEngine::ChunkManager::Update(float viewPosition[])
{
	// FIX DOUBLE LOADING OF CHUNKS
	// ADJUST SO CLOSEST CHUNKS ARE RENDERED FIRST
	// ADJUST SO FAR CHUNKS IN QUEUE ARE NEVER LOADED

	bool underChunk = false;
	bool northChunk = false;
	bool southChunk = false;
	bool eastChunk = false;
	bool westChunk = false;

	
	double offsetX = 8.0;
	double offsetZ = 8.0;
	if (viewPosition[0] < 0)
		offsetX *= -1.0;
	if (viewPosition[2] < 0)
		offsetZ *= -1.0;

	int cameraChunkPosition[3] = { (viewPosition[0] + offsetX) / voxelEngine::Chunk::s_SIZE, viewPosition[1] / voxelEngine::Chunk::s_HEIGHT, (viewPosition[2] + offsetZ) / voxelEngine::Chunk::s_SIZE };
	//std::cout << cameraChunkPosition[0] << ":" << cameraChunkPosition[2] << std::endl;

	for (int i = 0; i < activeChunks.size(); i++)
	{
		int pos[3];
		activeChunks[i]->GetPosition(pos);
		int distance = std::abs(cameraChunkPosition[0] - pos[0]) + std::abs(cameraChunkPosition[2] - pos[2]);
		if (distance > m_viewDistance + 1)
		{
			UnLoadChunk(i);
		}

		if (distance == 0)
			underChunk = true;

		if (cameraChunkPosition[0] == pos[0] && cameraChunkPosition[2] + 1 == pos[2])
			northChunk = true;

		if (cameraChunkPosition[0] == pos[0] && cameraChunkPosition[2] - 1 == pos[2])
			southChunk = true;

		if (cameraChunkPosition[0] + 1 == pos[0] && cameraChunkPosition[2] == pos[2])
			eastChunk = true;

		if (cameraChunkPosition[0] - 1 == pos[0] && cameraChunkPosition[2] == pos[2])
			westChunk = true;
	}

	for (int i = 0; i < loadQueue.size(); i++)
	{
		int pos[3];
		loadQueue[i]->GetPosition(pos);
		int distance = std::abs(cameraChunkPosition[0] - pos[0]) + std::abs(cameraChunkPosition[2] - pos[2]);

		if (distance == 0)
			underChunk = true;

		if (cameraChunkPosition[0] == pos[0] && cameraChunkPosition[2] + 1 == pos[2])
			northChunk = true;

		if (cameraChunkPosition[0] == pos[0] && cameraChunkPosition[2] - 1 == pos[2])
			southChunk = true;

		if (cameraChunkPosition[0] + 1 == pos[0] && cameraChunkPosition[2] == pos[2])
			eastChunk = true;

		if (cameraChunkPosition[0] - 1 == pos[0] && cameraChunkPosition[2] == pos[2])
			westChunk = true;
	}

	if (!underChunk)
	{
		LoadChunk(cameraChunkPosition[0], 0, cameraChunkPosition[2]);
	}

	if (!northChunk)
	{
		LoadChunk(cameraChunkPosition[0], 0, cameraChunkPosition[2] + 1);
	}

	if (!southChunk)
	{
		LoadChunk(cameraChunkPosition[0], 0, cameraChunkPosition[2] - 1);
	}

	if (!eastChunk)
	{
		LoadChunk(cameraChunkPosition[0] + 1, 0, cameraChunkPosition[2]);
	}

	if (!westChunk)
	{
		LoadChunk(cameraChunkPosition[0] - 1, 0, cameraChunkPosition[2]);
	}

	UpdateLoadQueue();

}

void voxelEngine::ChunkManager::UpdateLoadQueue()
{
	if (loadQueue.size() > 0)
	{
		int r = loadQueue[0]->Build();
		if (r == 1)
		{
			activeChunks.push_back(loadQueue[0]);
			loadQueue.erase(loadQueue.begin());
		}
	}
}

voxelEngine::ChunkManager::ChunkManager()
{
	for (int x = 0; x < m_viewDistance; x++)
	{
		for (int y = 0; y < m_viewDistance; y++)
		{
			LoadChunk(x - (m_viewDistance / 2), 0, y - (m_viewDistance / 2));
		}
	}
}

voxelEngine::ChunkManager::~ChunkManager()
{
	for (int i = 0; i < activeChunks.size(); i++)
	{
		delete activeChunks[i];
	}
}


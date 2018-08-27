#include "ChunkManager.h"

void voxelEngine::ChunkManager::LoadChunk(int x, int y, int z)
{
	Chunk* newChunk = new Chunk(x, y ,z, seed, m_VoxelsLoadedPerFrame);
	managedChunks[std::to_string(x) + ":" + std::to_string(z)] = newChunk;
	queueChunks.push_back(newChunk);
	std::cout << "Loading Chunk " << x << ":" << y << ":"<< z << std::endl;
}

void voxelEngine::ChunkManager::UnLoadChunk(int x, int z)
{
	Chunk* temp = managedChunks[std::to_string(x) + ":" + std::to_string(z)];

	for (int i = 0; i < activeChunks.size(); i++)
	{
		if (temp == activeChunks[i])
		{
			activeChunks.erase(activeChunks.begin() + i);
			break;
		}
	}

	managedChunks.erase(managedChunks.find(std::to_string(x) + ":" + std::to_string(z)));

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
	double offsetX = voxelEngine::Chunk::s_SIZE / 2;
	double offsetZ = voxelEngine::Chunk::s_SIZE / 2;
	if (viewPosition[0] < 0)
		offsetX *= -1.0;
	if (viewPosition[2] < 0)
		offsetZ *= -1.0;
	
	int cameraChunkPosition[3] = { (viewPosition[0] + offsetX) / voxelEngine::Chunk::s_SIZE, viewPosition[1] / voxelEngine::Chunk::s_HEIGHT, (viewPosition[2] + offsetZ) / voxelEngine::Chunk::s_SIZE };
	int cameraDelta[3] = {m_prevCameraPosition[0] - cameraChunkPosition[0], m_prevCameraPosition[1] - cameraChunkPosition[1] , m_prevCameraPosition[2] - cameraChunkPosition[2]};
	
	m_prevCameraPosition[0] = cameraChunkPosition[0]; m_prevCameraPosition[1] = cameraChunkPosition[1]; m_prevCameraPosition[2] = cameraChunkPosition[2];

	if (cameraDelta[0] != 0 || cameraDelta[2] != 0 || firstRun)
	{
		if (firstRun)
			firstRun = false;

		std::cout << "Camera Delta: " << cameraDelta[0] << ":" << cameraDelta[2] << std::endl;


		for (int i = 0; i < activeChunks.size(); i++)
		{
			// check if chunk is too far from player
			Chunk* temp = activeChunks[i];
			int pos[3];
			temp->GetPosition(pos);
			int distance = std::abs(cameraChunkPosition[0] - pos[0]) + std::abs(cameraChunkPosition[2] - pos[2]);
			// If farther then render distance + c then remove chunk

			if (distance > m_viewDistance + 6)
			{
				UnLoadChunk(pos[0], pos[2]);
			}
		}

		for (int i = 0; i < queueChunks.size(); i++)
		{
			// check if chunk is too far from player
			Chunk* temp = queueChunks[i];
			int pos[3];
			temp->GetPosition(pos);
			int distance = std::abs(cameraChunkPosition[0] - pos[0]) + std::abs(cameraChunkPosition[2] - pos[2]);

			// If farther then render distance + c then remove chunk

			if (distance > m_viewDistance + 4)
			{
				managedChunks.erase(managedChunks.find(std::to_string(pos[0]) + ":" + std::to_string(pos[2])));
				queueChunks.erase(queueChunks.begin() + i);
				delete temp;
			}
		}

		for (int x = -m_viewDistance + m_viewDistance / 2; x < m_viewDistance / 2; x++)
		{
			for (int z = -m_viewDistance + m_viewDistance / 2; z < m_viewDistance / 2; z++)
			{
				int chunkX = cameraChunkPosition[0] + x;
				int chunkZ = cameraChunkPosition[2] + z;

				// SLOW
				if (managedChunks.find(std::to_string(chunkX) + ":" + std::to_string(chunkZ)) != managedChunks.end())
				{

				}
				else
				{
					// Chunk being managed

					// Add to queue
					LoadChunk(chunkX, 0, chunkZ);
				}
			}
		}
	}

	UpdateLoadQueue(cameraChunkPosition);

}

void voxelEngine::ChunkManager::UpdateLoadQueue(int cameraChunkPosition[])
{
	if (queueChunks.size() > 0)
	{
		Chunk* temp = queueChunks[0];
		int r = temp->Build();

		if (r == 1)
		{
			
			int prevPos[3];
			temp->GetPosition(prevPos);
			std::cout << "Loaded Chunk " << prevPos[0] << ":" << prevPos[2] << std::endl;

			activeChunks.push_back(temp);
				
			queueChunks.erase(queueChunks.begin());
		}
	}
}

voxelEngine::ChunkManager::ChunkManager()
{
	/*
	for (int x = 0; x < m_viewDistance; x++)
	{
		for (int y = 0; y < m_viewDistance; y++)
		{
			LoadChunk(x - (m_viewDistance / 2), 0, y - (m_viewDistance / 2));
			loadedChunks[x][y] = nullptr;
		}
	}
	*/
}

voxelEngine::ChunkManager::~ChunkManager()
{
	for (int i = 0; i < activeChunks.size(); i++)
	{
		Chunk* temp = activeChunks[i];
		delete temp;
	}

	for (int i = 0; i < queueChunks.size(); i++)
	{
		Chunk* temp = queueChunks[i];
		delete temp;
	}
}

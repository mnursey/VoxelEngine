#include "Chunk.h"

voxelEngine::Chunk::Chunk(int chunkX, int chunkY, int chunkZ, int seed)
	: m_x(chunkX), m_y(chunkY), m_z(chunkZ), m_seed(seed)
{

	TerrainGenerator tGen(0);

	for (int x = 0; x < voxelEngine::Chunk::s_SIZE; x++)
	{
		for (int y = 0; y < voxelEngine::Chunk::s_HEIGHT; y++)
		{
			for (int z = 0; z < voxelEngine::Chunk::s_SIZE; z++)
			{
				m_pVoxels[x][y][z] = tGen.GetVoxelValue(x + chunkX * Chunk::s_SIZE, y + chunkY * Chunk::s_HEIGHT, z + chunkZ * Chunk::s_SIZE, chunkX, chunkZ);
			}
		}
	}
	built = true;
	GenerateRenderData();
}

voxelEngine::Chunk::Chunk(int chunkX, int chunkY, int chunkZ, int seed, int blocksPerFrame)
	: m_x(chunkX), m_y(chunkY), m_z(chunkZ), m_seed(seed), m_bpf(blocksPerFrame)
{

}

voxelEngine::Chunk::~Chunk()
{
	delete renderObject;
}

int voxelEngine::Chunk::Build()
{
	if (built)
		return 1;

	TerrainGenerator tGen(0);

	int blocksBuilt = 0;

	for (; m_currentX < voxelEngine::Chunk::s_SIZE; m_currentX++)
	{
		for (; m_currentY < voxelEngine::Chunk::s_HEIGHT; m_currentY++)
		{
			for (; m_currentZ < voxelEngine::Chunk::s_SIZE; m_currentZ++)
			{
				m_pVoxels[m_currentX][m_currentY][m_currentZ] = tGen.GetVoxelValue(m_currentX + m_x * Chunk::s_SIZE, m_currentY + m_y * Chunk::s_HEIGHT, m_currentZ + m_z * Chunk::s_SIZE, m_x, m_z);
				blocksBuilt++;
				if (blocksBuilt >= m_bpf)
				{
					m_currentZ++;
					return 0;
				}
			}
			m_currentZ = 0;
		}
		m_currentY = 0;
	}

	GenerateRenderData();
	built = true;
	return 1;
}

void voxelEngine::Chunk::GenerateRenderData()
{
	int m_vertexCount = 0;
	float* vertices = new float[s_SIZE * s_SIZE * s_HEIGHT * 6 * 6 * 10];

	int activeFaces = 0;
	for (int x = 0; x < s_SIZE; x++)
	{
		for (int y = 0; y < s_HEIGHT; y++)
		{
			for (int z = 0; z < s_SIZE; z++)
			{
				Voxel* current = &m_pVoxels[x][y][z];
				bool neighbours[6] = {false, false, false, false, false, false};
				ActiveNeighbours(x, y, z, neighbours);
				if (current->GetVoxelType() != 0)
				{
					for (int face = 0; face < 6; face++)
					{
						if (!neighbours[face])
						{
							// Add Face Verticies
							activeFaces++;
							for (int v = 0; v < 6; v++)
							{
								// Positions
								vertices[m_vertexCount * 10] =     VOXEL_POSITIONS[face * 36 + v * 6] + (x * Voxel::s_VOXEL_SIZE) + (m_x * s_SIZE) - s_SIZE / 2;
								vertices[m_vertexCount * 10 + 1] = VOXEL_POSITIONS[face * 36 + v * 6 + 1] + (y * Voxel::s_VOXEL_SIZE) + (m_y * s_SIZE);
								vertices[m_vertexCount * 10 + 2] = VOXEL_POSITIONS[face * 36 + v * 6 + 2] + (z * Voxel::s_VOXEL_SIZE) + (m_z * s_SIZE) - s_SIZE / 2;
								
								vertices[m_vertexCount * 10 + 3] = Block_Colors[current->GetVoxelType()][0] + current->m_moisture;
								vertices[m_vertexCount * 10 + 4] = Block_Colors[current->GetVoxelType()][1] + current->m_moisture;
								vertices[m_vertexCount * 10 + 5] = Block_Colors[current->GetVoxelType()][2] + current->m_moisture;
								vertices[m_vertexCount * 10 + 6] = Block_Colors[current->GetVoxelType()][3];
								
								// Normals
								vertices[m_vertexCount * 10 + 7] = VOXEL_POSITIONS[face * 36 + v * 6 + 3];
								vertices[m_vertexCount * 10 + 8] = VOXEL_POSITIONS[face * 36 + v * 6 + 4];
								vertices[m_vertexCount * 10 + 9] = VOXEL_POSITIONS[face * 36 + v * 6 + 5];

								m_vertexCount++;
							}
						}
					}
				}
			}
		}
	}

	//std::cout << "ACTIVE FACES: " << activeFaces << std::endl;

	VertexArray* chunkVA = new VertexArray();

	VertexBuffer* chunkVB = new VertexBuffer(vertices, m_vertexCount * 10 * sizeof(float));

	delete vertices;

	VertexBufferLayout* chunkLayout = new VertexBufferLayout();
	chunkLayout->Push<float>(3);
	chunkLayout->Push<float>(4);
	chunkLayout->Push<float>(3);
	chunkVA->AddBuffer(*chunkVB, *chunkLayout);

	delete chunkLayout;

	renderObject = new RenderObject(chunkVA, chunkVB, m_vertexCount);
}

void voxelEngine::Chunk::ActiveNeighbours(int x, int y, int z, bool* values)
{
	if (x < s_SIZE - 1)
	{
		Voxel a = m_pVoxels[x + 1][y][z];
		if (a.GetVoxelType() != BlockType_Air)
		{
			values[3] = true;
		}
	}

	if (x > 0)
	{
		Voxel a = m_pVoxels[x - 1][y][z];
		if (a.GetVoxelType() != BlockType_Air)
		{
			values[2] = true;
		}
	}

	if (y < s_HEIGHT - 1)
	{
		Voxel a = m_pVoxels[x][y + 1][z];
		if (a.GetVoxelType() != BlockType_Air)
		{
			values[5] = true;
		}
	}

	if (y > 0)
	{
		Voxel a = m_pVoxels[x][y - 1][z];
		if (a.GetVoxelType() != BlockType_Air)
		{
			values[4] = true;
		}
	}

	if (z < s_SIZE - 1)
	{
		Voxel a = m_pVoxels[x][y][z + 1];
		if (a.GetVoxelType() != BlockType_Air)
		{
			values[1] = true;
		}
	}

	if (z > 0)
	{
		Voxel a = m_pVoxels[x][y][z - 1];
		if (a.GetVoxelType() != BlockType_Air)
		{
			values[0] = true;
		}
	}
}

void voxelEngine::Chunk::Update(float delta)
{

}

void voxelEngine::Chunk::GetPosition(int* position)
{
	*position = m_x;
	*(position + 1) = m_y;
	*(position + 2) = m_z;
}
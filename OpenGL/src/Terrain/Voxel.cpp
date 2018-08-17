#include "Voxel.h"

voxelEngine::Voxel::Voxel()
	:m_blockType(BlockType_Air), m_x(0), m_y(0), m_z(0)
{

}

voxelEngine::Voxel::Voxel(BlockType type, int x, int y, int z, float moisture)
	:m_blockType(type), m_x(x), m_y(y), m_z(z), m_moisture(moisture)
{

}

voxelEngine::Voxel::~Voxel()
{

}

void voxelEngine::Voxel::GetPosition(int* x, int* y, int* z)
{
	(*x) = m_x;
	(*y) = m_y;
	(*z) = m_z;
}

int voxelEngine::Voxel::GetVoxelType()
{
	return m_blockType;
}

const int voxelEngine::Voxel::s_VOXEL_SIZE;

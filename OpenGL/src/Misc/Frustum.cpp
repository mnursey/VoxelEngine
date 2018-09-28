#include "Frustum.h"

Frustum::Frustum(glm::mat4 proj)
{
	planes[FRUSTUM_RIGHT].normal.x = proj[0][3] - proj[0][0];
	planes[FRUSTUM_RIGHT].normal.y = proj[1][3] - proj[1][0];
	planes[FRUSTUM_RIGHT].normal.z = proj[2][3] - proj[2][0];
	planes[FRUSTUM_RIGHT].distance = proj[3][3] - proj[3][0];

	planes[FRUSTUM_LEFT].normal.x = proj[0][3] + proj[0][0];
	planes[FRUSTUM_LEFT].normal.y = proj[1][3] + proj[1][0];
	planes[FRUSTUM_LEFT].normal.z = proj[2][3] + proj[2][0];
	planes[FRUSTUM_LEFT].distance = proj[3][3] + proj[3][0];

	planes[FRUSTUM_DOWN].normal.x = proj[0][3] + proj[0][1];
	planes[FRUSTUM_DOWN].normal.y = proj[1][3] + proj[1][1];
	planes[FRUSTUM_DOWN].normal.z = proj[2][3] + proj[2][1];
	planes[FRUSTUM_DOWN].distance = proj[3][3] + proj[3][1];

	planes[FRUSTUM_UP].normal.x = proj[0][3] - proj[0][1];
	planes[FRUSTUM_UP].normal.y = proj[1][3] - proj[1][1];
	planes[FRUSTUM_UP].normal.z = proj[2][3] - proj[2][1];
	planes[FRUSTUM_UP].distance = proj[3][3] - proj[3][1];

	planes[FRUSTUM_FAR].normal.x = proj[0][3] - proj[0][2];
	planes[FRUSTUM_FAR].normal.y = proj[1][3] - proj[1][2];
	planes[FRUSTUM_FAR].normal.z = proj[2][3] - proj[2][2];
	planes[FRUSTUM_FAR].distance = proj[3][3] - proj[3][2];

	planes[FRUSTUM_NEAR].normal.x = proj[0][3] + proj[0][2];
	planes[FRUSTUM_NEAR].normal.y = proj[1][3] + proj[1][2];
	planes[FRUSTUM_NEAR].normal.z = proj[2][3] + proj[2][2];
	planes[FRUSTUM_NEAR].distance = proj[3][3] + proj[3][2];

	for (int i = 0; i < 6; i++)
	{
		planes[i].Normalize();
	}
}

bool Frustum::FrustumCulling(glm::vec3 point, float r)
{
	for (int i = 0; i < 6; i++)
	{
		if (glm::dot(point, planes[i].normal) + planes[i].distance + r <= 0)
		{
			return false;
		}
	}

	return true;
}
#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <math.h>
#include "Plane.h"


#define FRUSTUM_NEAR	0
#define FRUSTUM_FAR		1
#define FRUSTUM_LEFT	2
#define FRUSTUM_RIGHT	3
#define FRUSTUM_UP		4
#define FRUSTUM_DOWN	5

class Frustum {

	Plane planes[6];

public:
	Frustum(glm::mat4 proj);

	bool FrustumCulling(glm::vec3 point, float r);
};

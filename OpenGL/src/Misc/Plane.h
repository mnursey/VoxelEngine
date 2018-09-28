#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <math.h>

// The Plane class defined by a normal vector which should always be unit length and a distance d from the origin.
// Also can be thought of as ax + by + cz + d = 0, the equation of a plane in 3D space, where a, b, and c are the x, y, z, of the normal.

class Plane {
public:
	Plane(glm::vec3 n, double d);
	Plane();
	void Normalize();

	glm::vec3 normal;
	// Distance from origin
	double distance;
};
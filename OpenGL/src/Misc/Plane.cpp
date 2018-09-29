#include "Plane.h"

Plane::Plane(glm::vec3 n, double d) : normal(n), distance(d) {}

Plane::Plane() {}

void Plane::Normalize()
{
	double scale = 1 / glm::length(normal);
	normal.x *= scale;
	normal.y *= scale;
	normal.z *= scale;
	distance *= scale;

}

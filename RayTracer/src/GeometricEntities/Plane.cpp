#include "Plane.h"


Plane::Plane(Vector3 normal)
{
	Normal = normal;
	SurfacePointA = Vector3(0.0f, 0.0f, 0.0f);
}

Plane::~Plane()
{
}

float Plane::Intersect(Ray ray)
{
	return (SurfacePointA - ray.origin).DotProduct(Normal) / (ray.direction.DotProduct(Normal));
}

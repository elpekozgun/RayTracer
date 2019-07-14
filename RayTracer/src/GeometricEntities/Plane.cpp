#include "Plane.h"


Plane::Plane(Vector3 normal,Vector3 surfacePoint)
{
	Normal = normal;
	SurfacePoint = surfacePoint;
}

Plane::~Plane()
{
}

float Plane::Intersect(Ray ray)
{
	return (SurfacePoint - ray.origin).DotProduct(Normal) / (ray.direction.DotProduct(Normal));
}

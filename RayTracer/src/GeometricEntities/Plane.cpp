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

Vector3 Plane::GetNormal(Vector3 Point)
{
	return Normal;
}

int Plane::ID()
{
	return 0;
}

int Plane::MaterialID()
{
	return 0;
}

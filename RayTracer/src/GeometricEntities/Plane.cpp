#include "Plane.h"


Plane::Plane(Vector3 normal,Vector3 surfacePoint)
{
	Normal = normal;
	SurfacePoint = surfacePoint;
}

Plane::~Plane()
{
}

IGeometricEntity* Plane::Intersect(Ray ray, float& t)
{
	t = (SurfacePoint - ray.origin).DotProduct(Normal) / (ray.direction.DotProduct(Normal));
	return this;
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

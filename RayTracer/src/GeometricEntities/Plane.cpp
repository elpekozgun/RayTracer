#include "Plane.h"


Plane::Plane(Vector3 normal,Vector3 surfacePoint)
{
	Normal = normal;
	SurfacePoint = surfacePoint;
}

Plane::~Plane()
{
}

std::pair<float, IGeometricEntity*> Plane::Intersect(Ray ray)
{
	return std::pair<float,IGeometricEntity*>((SurfacePoint - ray.origin).DotProduct(Normal) / (ray.direction.DotProduct(Normal)),this);
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

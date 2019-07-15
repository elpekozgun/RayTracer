#include "Sphere.h"
#include <cmath>

Sphere::Sphere()
{
	Id = -1;
	MaterialId = -1;
	Center = Vector3();
	Radius = 0.0f;
}

Sphere::Sphere(int id, int materialId, Vector3 center, float radius)
{
	Id = id;
	MaterialId = materialId;
	Center = center;
	Radius = radius;
}

Sphere::~Sphere()
{
}

float Sphere::Intersect(Ray ray)
{
	float dd = ray.direction.DotProduct(ray.direction);
	Vector3	 o_c = ray.origin - Center;
	float do_c = ray.direction.DotProduct(o_c);

	float t1 = (-do_c + sqrt(powf(do_c, 2.0f) + dd * (o_c.DotProduct(o_c) - Radius * Radius))) / dd;
	float t2 = (-do_c + sqrt(powf(do_c, 2.0f) - dd * (o_c.DotProduct(o_c) - Radius * Radius))) / dd;

	return t1 <= t2 ? t1 : t2;
}

eEntityType Sphere::GetType()
{
	return eEntityType::sphere;
}

int Sphere::ID()
{
	return Id;
}

int Sphere::MaterialID()
{
	return MaterialId;
}

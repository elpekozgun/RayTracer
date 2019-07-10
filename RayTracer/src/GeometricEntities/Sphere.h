#pragma once
#include "IGeometricEntity.h"

class Sphere : public IGeometricEntity
{
public:

	Vector3 Center;
	float Radius;
	

	Sphere(Vector3 center, float radius);
	~Sphere();

	virtual float Intersect(Ray ray) override;

};


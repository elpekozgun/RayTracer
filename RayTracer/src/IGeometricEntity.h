#pragma once
#include "Ray.h"

class IGeometricEntity
{
public:
	virtual ~IGeometricEntity() {};

	virtual float Intersect(Ray ray) = 0;

};

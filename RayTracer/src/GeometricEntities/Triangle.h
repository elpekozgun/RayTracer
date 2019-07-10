#pragma once
#include "IGeometricEntity.h"

class Triangle : public IGeometricEntity
{
public:
	Triangle();
	~Triangle();


	virtual float Intersect(Ray ray) override;

};


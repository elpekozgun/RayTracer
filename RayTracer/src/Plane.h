#pragma once	
#include "IGeometricEntity.h"

class Plane : public IGeometricEntity 
{
public:
	Plane();
	~Plane();

	virtual float Intersect(Ray ray) override;

private:

};

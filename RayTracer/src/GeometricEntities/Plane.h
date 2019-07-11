#ifndef PLANE_H
#define PLANE_H

#include "IGeometricEntity.h"

class Plane : public IGeometricEntity 
{
public:

	Vector3 Normal;
	Vector3 SurfacePointA;

	Plane(Vector3 normal);
	~Plane();

	
	virtual float Intersect(Ray ray) override;

};

#endif

#ifndef PLANE_H
#define PLANE_H

#include "IGeometricEntity.h"

class Plane : public IGeometricEntity 
{
public:

	Vector3 Normal;
	Vector3 SurfacePoint;

	Plane(Vector3 normal, Vector3 surfacePoint);
	~Plane();

	
	virtual float Intersect(Ray ray) override;
	virtual int ID() override;
	virtual int MaterialID() override;

};

#endif

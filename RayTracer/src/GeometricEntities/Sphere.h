#ifndef SPHERE_H
#define SPHERE_H

#include "IGeometricEntity.h"

class Sphere : public IGeometricEntity, IEntity
{
public:

	int ID;
	int MaterialID;
	int VertexID;
	Vector3 Center;
	float Radius;
	
	Sphere();
	Sphere(Vector3 center, float radius);
	~Sphere();

	virtual float Intersect(Ray ray) override;


	// Inherited via IEntity
	virtual eEntityType GetType() override;

};

#endif



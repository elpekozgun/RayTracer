#ifndef SPHERE_H
#define SPHERE_H

#include "IGeometricEntity.h"

class Sphere : public IGeometricEntity, IEntity
{
public:

	Vector3 Center;
	float Radius;
	
	Sphere();
	Sphere(int id, int materialId, Vector3 center, float radius);
	~Sphere();

	
	virtual eEntityType GetType() override;

	virtual float Intersect(Ray ray) override;
	virtual int ID() override;
	virtual int MaterialID() override;
private:
	int Id;
	int MaterialId;
};

#endif



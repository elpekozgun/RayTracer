#ifndef SPHERE_H
#define SPHERE_H

#include "IGeometricEntity.h"
#include "../Entities/Material.h"

class Sphere : public IGeometricEntity, IEntity
{
public:

	Vector3 Center;
	float Radius;
	Material* Material;

	
	Sphere();
	Sphere(int id, int materialId, Vector3 center, float radius);
	~Sphere();

	
	// IEntity
	virtual eEntityType GetType() override;

	//  IGeometricEntity
	virtual float Intersect(Ray ray) override;
	virtual Vector3 GetNormal(Vector3 point) override;
	virtual int ID() override;
	virtual int MaterialID() override;

private:
	int Id;
	int MaterialId;
};

#endif



#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "IGeometricEntity.h"

class Triangle : public IGeometricEntity, IEntity
{
public:

	Vector3 Vertices[3];
	int ID;
	int MaterialID;


	Triangle();
	~Triangle();


	virtual float Intersect(Ray ray) override;


	// Inherited via IEntity
	virtual eEntityType GetType() override;

};

#endif 
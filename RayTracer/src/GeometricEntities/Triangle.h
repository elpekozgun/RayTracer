#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Plane.h"
#include "..////Core/Matrix3.h"
#include "../Entities/Material.h"

class Triangle : public IGeometricEntity, IEntity
{
public:

	Vector3 Vertices[3];

	Triangle();
	Triangle(int id, int materialId, Vector3 vertices[3]);
	~Triangle();

	vector<Triangle*> neighbors;


	Vector3 GetCenter();


	// IEntity
	virtual eEntityType GetType() override;

	// IGeometricEntity
	virtual std::pair<float, IGeometricEntity*> Intersect(Ray ray) override;
	virtual Vector3 GetNormal(Vector3 Point) override;
	virtual int ID() override;
	virtual int MaterialID() override;

private:
	int Id;
	int MaterialId;
	
};

#endif 
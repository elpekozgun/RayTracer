#ifndef MESH_H
#define MESH_H

#include <vector>
#include <algorithm>

#include "IGeometricEntity.h"
#include "Triangle.h"
#include "Box.h"

enum class ePartitionAxis
{
	X = 0,
	Y = 1,
	Z = 2
};

class Mesh : public IGeometricEntity , IEntity
{
public:

	Mesh();
	Mesh(int id, int materialID, std::vector<Triangle*>& triangles, ePartitionAxis currentAxis);
	~Mesh() override;

	std::vector<Triangle*> Triangles;
	Box Boundingbox;
	Mesh* Left;
	Mesh* Right;

	virtual eEntityType GetType() override;
	
	IGeometricEntity* Intersect(Ray ray,float& t) override;
	virtual Vector3 GetNormal(Vector3 point) override;
	virtual int ID() override;
	virtual int MaterialID() override;

private:
	int Id;
	int MaterialId;

	Box CalculateBoundingBox(std::vector<Triangle*> triangles);
	void SortPoints(std::vector<Triangle*>& triangles, ePartitionAxis axis);
	ePartitionAxis NextAxis(ePartitionAxis axis);

	Vector3 hitObjectNormal;
};


#endif


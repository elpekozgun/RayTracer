#ifndef MESH_H
#define MESH_H

#include <vector>
#include "IGeometricEntity.h"

class Mesh : public IGeometricEntity , IEntity
{
	std::vector<Vector3> Vertices;


public:
	Mesh();
	Mesh(int id);
	~Mesh();


	float Intersect(Ray ray) override;

	virtual eEntityType GetType() override;

};


#endif


#ifndef MESH_H
#define MESH_H

#include <vector>
#include "IGeometricEntity.h"
#include "Triangle.h"

class Mesh : public IGeometricEntity , IEntity
{
public:

	int ID;
	int MaterialID;
	std::vector<Triangle> Triangles;


	Mesh();
	Mesh(int id);
	~Mesh();


	float Intersect(Ray ray) override;

	virtual eEntityType GetType() override;

};


#endif


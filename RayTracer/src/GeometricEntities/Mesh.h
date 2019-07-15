#ifndef MESH_H
#define MESH_H

#include <vector>
#include "IGeometricEntity.h"
#include "Triangle.h"

class Mesh : public IGeometricEntity , IEntity
{
public:


	std::vector<Triangle> Triangles;


	Mesh();
	Mesh(int id, int materialID);
	~Mesh();


	float Intersect(Ray ray) override;

	virtual eEntityType GetType() override;
	virtual int ID() override;
	virtual int MaterialID() override;
private:
	int Id;
	int MaterialId;
};


#endif


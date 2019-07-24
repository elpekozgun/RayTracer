#ifndef MESH_H
#define MESH_H

#include <vector>
#include "IGeometricEntity.h"
#include "Triangle.h"
#include "..//Core/KdNode.h"

class Mesh : public IGeometricEntity , IEntity
{
public:

	std::vector<Triangle*> Triangles;





	Mesh();
	Mesh(int id, int materialID);
	~Mesh() override;

	// IEntity
	virtual eEntityType GetType() override;
	
	// IGeometricEntity
	std::pair<float, IGeometricEntity*> Intersect(Ray ray) override;
	virtual Vector3 GetNormal(Vector3 point) override;
	virtual int ID() override;
	virtual int MaterialID() override;

private:
	int Id;
	int MaterialId;

	Vector3 hitObjectNormal;
};


#endif


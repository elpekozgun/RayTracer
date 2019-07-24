#ifndef KDNODE_H
#define KDNODE_H

#include <vector>
#include <algorithm>

#include "..//GeometricEntities/Box.h"
#include "..//GeometricEntities/Mesh.h"

#include "Vector3.h"

enum class ePartitionAxis
{
	X = 0,
	Y = 1,
	Z = 2
};

class KdNode : IGeometricEntity
{
public:
	int materialId;

	KdNode(std::vector<Triangle*>& triangles, ePartitionAxis currentAxis);
	~KdNode();

	std::vector<Triangle*> Triangles;

	Box Boundingbox;
	KdNode* Left;
	KdNode* Right;

	//KdNode* MakeKdTree(std::vector<Triangle*>, ePartitionAxis currentAxis);

private:

	Box CalculateBoundingBox(std::vector<Triangle*> triangles);
	void SortPoints(std::vector<Triangle*>& triangles, ePartitionAxis axis);
	ePartitionAxis NextAxis(ePartitionAxis axis);


	// Inherited via IGeometricEntity
	
	virtual std::pair<float, IGeometricEntity*> Intersect(Ray ray) override;

	virtual int ID() override;

	virtual int MaterialID() override;

	virtual Vector3 GetNormal(Vector3 point) override;


	

};

#endif 

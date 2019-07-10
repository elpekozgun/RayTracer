#pragma once
#include <vector>
#include "IGeometricEntity.h"

class Mesh : public IGeometricEntity
{
	std::vector<Vector3> Vertices;


public:
	Mesh();
	~Mesh();

	
	virtual float Intersect(Ray ray) override;

};


#include "Triangle.h"

Triangle::Triangle()
{
	Vertices[0] = Vector3();
	Vertices[1] = Vector3();
	Vertices[2] = Vector3();

	ID = -1;
	MaterialID = -1;
}

Triangle
::~Triangle()
{
}

float Triangle::Intersect(Ray ray)
{
	return 0.0f;
}

eEntityType Triangle::GetType()
{
	return eEntityType::triangle;
}

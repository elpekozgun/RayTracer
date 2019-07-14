#include "Triangle.h"

Triangle::Triangle()
{
	Vertices[0] = Vector3();
	Vertices[1] = Vector3();
	Vertices[2] = Vector3();

	ID = -1;
	MaterialID = -1;
}

Triangle::Triangle(int id, int materialId, Vector3 vertices[3])
{
	ID= id;
	MaterialID = materialId;
	Vertices[0] = vertices[0];
	Vertices[1] = vertices[1];
	Vertices[2] = vertices[2];
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

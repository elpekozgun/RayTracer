#include "Triangle.h"

Triangle::Triangle()
{
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

#include "Ray.h"

Ray::Ray(Vector3 origin, Vector3 direction)
{
	this->origin = origin;
	this->direction = direction;
}

Ray::~Ray()
{
}

#include "Ray.h"

Ray::Ray(Vector3 origin, Vector3 direction, bool isShadowRay)
{
	this->origin = origin;
	this->direction = direction;
	this->IsShadowRay = isShadowRay;
}

Ray::~Ray()
{
}

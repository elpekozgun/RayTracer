#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

class Ray
{
public:

	Vector3 origin;
	Vector3 direction;
	bool IsShadowRay;

	Ray(Vector3 origin, Vector3 direction,bool isShadowRay);
	~Ray();

};

#endif 


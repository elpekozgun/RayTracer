#pragma once
#include "Vector3.h"

class Ray
{
public:

	Vector3 origin;
	Vector3 direction;

	Ray(Vector3 origin, Vector3 direction);
	~Ray();

};


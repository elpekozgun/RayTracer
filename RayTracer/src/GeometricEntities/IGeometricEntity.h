#ifndef IGEOMETRICENTITY_H
#define IGEOMETRICENTITY_H

#include "../Core/Ray.h"
#include "..//Core/IEntity.h"

class IGeometricEntity
{

public:
	virtual float Intersect(Ray ray) = 0;
};

#endif 


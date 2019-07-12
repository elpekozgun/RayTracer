#ifndef IGEOMETRICENTITY_H
#define IGEOMETRICENTITY_H

#include "../Core/Ray.h"
#include "..//Entities/IEntity.h"

class IGeometricEntity
{

public:
	virtual float Intersect(Ray ray) = 0;
};

#endif 


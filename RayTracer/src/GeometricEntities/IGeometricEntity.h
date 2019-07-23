#ifndef IGEOMETRICENTITY_H
#define IGEOMETRICENTITY_H

#include "../Core/Ray.h"
#include "..//Entities/IEntity.h"
#include <iostream>

class IGeometricEntity
{

public:
	virtual std::pair<float,IGeometricEntity*> Intersect(Ray ray) = 0;
	virtual Vector3 GetNormal(Vector3 point) = 0;
	virtual int ID() = 0;
	virtual int MaterialID() = 0;
	
	virtual ~IGeometricEntity() = 0;


};


#endif 


#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <vector>
#include "IEntity.h"
#include "../Core/Vector3.h"

class PointLight : public IEntity
{
public:

	Vector3 Position;
	Vector3 Intensity;
	int ID;

	PointLight();
	~PointLight();

	virtual eEntityType GetType() override;



};

#endif 


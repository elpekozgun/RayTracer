#include "PointLight.h"

PointLight::PointLight()
{
	Position = Vector3();
	Intensity = Vector3();
	ID = -1;
}

PointLight::~PointLight()
{
}

eEntityType PointLight::GetType()
{
	return eEntityType();
}

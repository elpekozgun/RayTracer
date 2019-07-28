#include "PointLight.h"

PointLight::PointLight()
{
	Position = Vector3();
	Intensity = Vector3();
	ID = -1;
}

PointLight::~PointLight()
{
	//std::cout << "Point light " << ID << " deleted" << std::endl;
}

eEntityType PointLight::GetType()
{
	return eEntityType::pointlight;
}

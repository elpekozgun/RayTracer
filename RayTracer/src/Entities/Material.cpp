#include "Material.h"

Material::Material()
{
	ID = -1;
	Ambient = Vector3::Zero();
	Diffuse = Vector3::Zero();
	Specular = Vector3::Zero();
	PhongExponent = 0.0f;
	MirrorReflectance = Vector3::Zero();
	Refraction = 0.0f;
}

Material::~Material()
{
	//std::cout << "Material " << ID << " deleted" << std::endl;
}

eEntityType Material::GetType()
{
	return eEntityType::material;
}



#include "Material.h"

Material::Material()
{
	ID = -1;
	Ambient = Vector3();
	Diffuse = Vector3();
	Specular = Vector3();
	PhongExponent = 0;
	MirrorReflectance = Vector3();
}

Material::~Material()
{
	std::cout << "Material " << ID << " deleted" << std::endl;
}

eEntityType Material::GetType()
{
	return eEntityType::material;
}



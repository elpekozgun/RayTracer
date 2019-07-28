#ifndef MATERIAL_H
#define MATERIAL_H

#include "IEntity.h"
#include "..//Core/Vector3.h"

class Material : public IEntity
{
public:
	int ID;
	Vector3 Ambient;
	Vector3 Diffuse;
	Vector3 Specular;
	Vector3 MirrorReflectance;
	float PhongExponent;
	float Refraction;

	Material();
	~Material();
	

	// Inherited via IEntity
	virtual eEntityType GetType() override;

};

#endif // !MATERIAL_H

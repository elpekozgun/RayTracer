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
	float PhongExponent;
	Vector3 MirrorReflectance;

	Material();
	~Material();
	

	// Inherited via IEntity
	virtual eEntityType GetType() override;

};

#endif // !MATERIAL_H

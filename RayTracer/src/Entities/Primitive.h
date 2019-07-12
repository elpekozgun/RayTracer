#ifndef PRIMITIVE_H
#define PRIMITIVE_H


#include "..//Core/Vector3.h"
#include "IEntity.h"


class BackgroundColor : public IEntity
{
public:

	Vector3 BackgroundColorValue;

	BackgroundColor();
	~BackgroundColor();

	virtual eEntityType GetType() override;

};

class AmbientLight : public IEntity 
{
public:

	Vector3 AmbientLightValue;

	AmbientLight();
	~AmbientLight();

	virtual eEntityType GetType() override;

};

class ShadowRayEpsilon : public IEntity
{
public:

	float ShadowRayEpsilonValue;

	ShadowRayEpsilon();
	~ShadowRayEpsilon();

	virtual eEntityType GetType() override;

};

class MaxRecursionDepth : public IEntity
{
public:

	int MaxRecursionDepthValue;

	MaxRecursionDepth();
	~MaxRecursionDepth();

	virtual eEntityType GetType() override;

};

#endif 

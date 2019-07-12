#include "Primitive.h"

BackgroundColor::BackgroundColor()
{
	BackgroundColorValue = Vector3();
}

BackgroundColor::~BackgroundColor()
{
}

eEntityType BackgroundColor::GetType()
{
	return eEntityType::backgroundColor;
}

AmbientLight::AmbientLight()
{
	AmbientLightValue = Vector3();
}

AmbientLight::~AmbientLight()
{
}

eEntityType AmbientLight::GetType()
{
	return eEntityType::ambientLight;
}

ShadowRayEpsilon::ShadowRayEpsilon()
{
	ShadowRayEpsilonValue = 0.0f;
}

ShadowRayEpsilon::~ShadowRayEpsilon()
{
}

eEntityType ShadowRayEpsilon::GetType()
{
	return eEntityType::shadowRayEpsilon;
}

MaxRecursionDepth::MaxRecursionDepth()
{
	MaxRecursionDepthValue = 0;
}

MaxRecursionDepth::~MaxRecursionDepth()
{
}

eEntityType MaxRecursionDepth::GetType()
{
	return eEntityType::maxRecursionDepth;
}


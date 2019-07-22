#include "Primitive.h"

BackgroundColor::BackgroundColor()
{
	BackgroundColorValue = Vector3();
}

BackgroundColor::~BackgroundColor()
{
	std::cout << "Background color deleted " << std::endl;
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
	std::cout << "Ambient light deleted " << std::endl;
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
	std::cout << "Shadow Ray Epsilon deleted " << std::endl;
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
	std::cout << "max recursion depth deleted " << std::endl;
}

eEntityType MaxRecursionDepth::GetType()
{
	return eEntityType::maxRecursionDepth;
}

Scene::Scene(Vector3 backgroundColor, Vector3 ambientLight, std::vector<PointLight> pointLights, int recursionDepth, float shadowRayEpsilon)
{
	this->BackgroundColor = backgroundColor;
	this->AmbientLight = ambientLight;
	this->PointLights = pointLights;
	this->RecursionDepth = recursionDepth;
	this->ShadowRayEpsilon = shadowRayEpsilon;
}

Scene::Scene()
{
	RecursionDepth = 0;
	ShadowRayEpsilon = 0.0f;
}


Scene::~Scene()
{
}

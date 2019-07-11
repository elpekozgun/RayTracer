#include "ValueType.h"

eEntityType BackgroundColor::GetType()
{
	return eEntityType::background;
}

eEntityType MaxRecursionDepth::GetType()
{
	return eEntityType::maxrecursiondepth;
}

eEntityType ShadowRayEpsilon::GetType()
{
	return eEntityType::shadowrayepsilon;
}

eEntityType AmbientLight::GetType()
{
	return eEntityType::ambientlight;
}

eEntityType VertexList::GetType()
{
	return eEntityType::vertexlist;
}

eEntityType PointLight::GetType()
{
	return eEntityType::pointlight;
}

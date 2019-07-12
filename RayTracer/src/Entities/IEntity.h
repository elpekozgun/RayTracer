#ifndef IENTITY_H
#define IENTITY_H


enum class eEntityType : char
{
	invalid = 0,
	backgroundColor = 1,
	maxRecursionDepth = 2,
	shadowRayEpsilon = 3,
	camera = 4,
	material = 5,
	ambientLight = 6,
	pointlight = 7,
	vertexlist = 8,
	sphere = 9,
	triangle = 10,
	mesh = 11,
	sceneItem = 12

};



class IEntity
{
public:
	virtual eEntityType GetType() = 0;

};


#endif // !IENTITY_H

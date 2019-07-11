#ifndef IENTITY_H
#define IENTITY_H

enum class eEntityType : char
{
	background = 0,
	maxrecursiondepth = 1,
	shadowrayepsilon = 2,
	camera = 3,
	material = 4,
	ambientlight = 5,
	pointlight = 6,
	vertexlist = 7,
	sphere = 8,
	triangle = 9,
	mesh = 10

};



class IEntity
{
public:
	virtual eEntityType GetType() = 0;

};


#endif // !IENTITY_H

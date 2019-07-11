#ifndef VALUETYPE_H
#define VALUETYPE_H

#include "IEntity.h"
#include "Vector3.h"
#include <vector>

class BackgroundColor : public IEntity

{
public:
	Vector3 Color;

	virtual eEntityType GetType() override;

};

class MaxRecursionDepth : public IEntity
{
public:

	int RecursionDepth;

	virtual eEntityType GetType() override;

};

class ShadowRayEpsilon : public IEntity
{
public:

	int ShadowRayEpsilon;

	virtual eEntityType GetType() override;

};

class AmbientLight: public IEntity
{
public:

	Vector3 AmbientColor;

	virtual eEntityType GetType() override;

};

class PointLight : public IEntity
{
public:

	int ID;
	Vector3 position;
	Vector3 Intensity;

	virtual eEntityType GetType() override;

};

class VertexList : public IEntity
{
	public:
		std::vector<Vector3> vertexList;

		virtual eEntityType GetType() override;
};



#endif // !VALUETYPE_H


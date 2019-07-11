#ifndef VALUETYPE_H
#define VALUETYPE_H

#include "IEntity.h"
#include "vecto

class BackgroundColor : public IEntity

{
public:
	vector3

	// Inherited via IEntity
	virtual eEntityType GetType() override;

};

class MaxRecursionDepth : public IEntity

{
public:
	int recursionDepth;

	// Inherited via IEntity
	virtual eEntityType GetType() override;

};





#endif // !VALUETYPE_H


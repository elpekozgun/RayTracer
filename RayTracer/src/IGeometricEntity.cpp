#pragma once

class IGeometricEntity
{
public:
	virtual ~IGeometricEntity() {};

	float virtual Intersect();

};


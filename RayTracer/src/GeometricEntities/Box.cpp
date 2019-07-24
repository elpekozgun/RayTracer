#include "Box.h"

Box::Box()
{
}

Box::Box(const Vector3 vMin, const Vector3 vMax)
{
	Id = -1;
	MaterialId = -1;
	bounds[0] = vMin;
	bounds[1] = vMax;
}

Box::~Box()
{
	//std::cout << "Bounding box : " << ID() << " deleted";
}

std::pair<float, IGeometricEntity*> Box::Intersect(Ray ray)
{
	
	float tMin = (bounds[0].X - ray.origin.X) / ray.direction.Normalized().X;
	float tMax = (bounds[1].X - ray.origin.X) / ray.direction.Normalized().X;

	if(tMin > tMax)
	{
		std::swap(tMin, tMax);
	}

	float tYMin = (bounds[0].Y - ray.origin.Y) / ray.direction.Normalized().Y;
	float tYMax = (bounds[1].Y - ray.origin.Y) / ray.direction.Normalized().Y;

	if(tYMin > tYMax)
	{
		std::swap(tYMin, tYMax);
	}

	if(tMin > tYMax || tYMin > tMax)
	{
		return std::pair<float, IGeometricEntity*>(0,NULL);
	}

	if(tYMin > tMin)
	{
		tMin = tYMin;
	}

	if(tYMax < tMax)
	{
		tMax = tYMax;
	}

	float tZMin = (bounds[0].Z - ray.origin.Z) / ray.direction.Normalized().Z;
	float tZMax = (bounds[1].Z - ray.origin.Z) / ray.direction.Normalized().Z;

	if(tZMin > tZMax)
	{
		std::swap(tZMin, tZMax);
	}

	if(tMin > tZMax || tZMin > tMax)
	{
		return std::pair<float, IGeometricEntity*>(0, NULL);
	}

	if(tZMin > tMin)
	{
		tMin = tZMin;
	}

	if(tZMax < tMax)
	{
		tMax = tZMax;
	}

	if(tMin > tMax)
	{
		std::swap(tMin, tMax);
	}

	return std::pair<float, IGeometricEntity*>(tMin, this);
}

Vector3 Box::GetNormal(Vector3 point)
{
	return Vector3::Zero();
}

int Box::ID()
{
	return this->Id;
}

int Box::MaterialID()
{
	return this->MaterialId;
}

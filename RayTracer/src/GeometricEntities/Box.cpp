#include "Box.h"

Box::Box()
{
	Id = -1;
	MaterialId = -1;
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
	//std::cout << "Bounding box : " << ID() << " deleted \n";
}

bool Box::isPointInside(Vector3 point)
{
	return	point.X <= bounds[1].X && point.X >= bounds[0].X &&
			point.Y <= bounds[1].Y && point.Y >= bounds[0].Y &&
			point.Z <= bounds[1].Z && point.Z >= bounds[0].Z;

}

std::pair<float, IGeometricEntity*> Box::Intersect(Ray ray)
{
	float inverseX = 1 / (ray.direction.X);
	float inverseY = 1 / (ray.direction.Y);
	float inverseZ = 1 / (ray.direction.Z);

	float tMin = (bounds[0].X - ray.origin.X) * inverseX;
	float tMax = (bounds[1].X - ray.origin.X) * inverseX;

	if(tMin > tMax)
	{
		std::swap(tMin, tMax);
	}

	float tYMin = (bounds[0].Y - ray.origin.Y) * inverseY;
	float tYMax = (bounds[1].Y - ray.origin.Y) * inverseY;

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

	float tZMin = (bounds[0].Z - ray.origin.Z) * inverseZ;
	float tZMax = (bounds[1].Z - ray.origin.Z) * inverseZ;

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

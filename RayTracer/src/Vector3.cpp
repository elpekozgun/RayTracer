#include "Vector3.h"
#include <cmath>

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

float Vector3::DotProduct(Vector3 other)
{
	return this->x* other.x + this->y * other.y + this->z * other.z;
}

float Vector3::DotProductNormalized(Vector3 other)
{
	float a = sqrtf((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
	float b = sqrtf((other.x * other.x) + (other.y * other.y) + (other.z * other.z));
	return this->DotProduct(other) / (a * b);
}

Vector3 Vector3::CrossProduct(Vector3 other)
{
	float x = this->y * other.z - this->z * other.y;
	float y = this->z * other.x - this->x * other.z;
	float z = this->x * other.y - this->y * other.x;

	return Vector3(x, y, z);
}

float Vector3::DistanceToOther(Vector3 other)
{
	return 0.0f;
}

Vector3::~Vector3()
{
}

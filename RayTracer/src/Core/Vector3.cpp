#include "Vector3.h"

Vector3::Vector3(float x, float y, float z)
{
	this->X = x;
	this->Y = y;
	this->Z = z;
}

Vector3::Vector3()
{
	this->X = 0;
	this->Y = 0;
	this->Z = 0;
}

Vector3 Vector3::Zero()
{
	return Vector3(0.0f, 0.0f, 0.0f);
}

float Vector3::DotProduct(Vector3 other)
{
	return this->X * other.X + this->Y * other.Y + this->Z * other.Z;
}

float Vector3::DotProductNormalized(Vector3 other)
{
	float a = this->Length();
	float b = other.Length();
	return this->DotProduct(other) / (a * b);
}

Vector3 Vector3::CrossProduct(Vector3 other)
{
	float x = this->Y * other.Z - this->Z * other.Y;
	float y = this->Z * other.X - this->X * other.Z;
	float z = this->X * other.Y - this->Y * other.X;

	return Vector3(x, y, z);
}

float Vector3::Length()
{
	return sqrt(this->X * this->X + this->Y * this->Y + this->Z * this->Z);
}

Vector3 Vector3::Normalized()
{
	float magnitude = sqrtf(X * X + Y * Y + Z * Z);

	return Vector3(X / magnitude, Y / magnitude, Z / magnitude);
}

float Vector3::DistanceTo(Vector3 other)
{
	return (*this - other).Length();
}

Vector3::~Vector3()
{
}

#ifndef VECTOR_3_H
#define VECTOR_3_H
#include <cmath>


class Vector3
{
public:
	float X;
	float Y;
	float Z;


	Vector3(float x, float y, float z);
	Vector3();

	static Vector3 Zero();


	float DotProduct(Vector3 other);
	float DotProductNormalized(Vector3 other);
	Vector3 CrossProduct(Vector3 other);
	float Magnitude();
	float Length();
	Vector3 Normalized();

	inline Vector3 operator + (const Vector3& p) const { return Vector3(this->X + p.X, this->Y + p.Y, this->Z + p.Z); }
	inline Vector3 operator - (const Vector3& p) const { return Vector3(this->X - p.X, this->Y - p.Y, this->Z - p.Z); }
	inline Vector3 operator / (const float& f) const   { return Vector3(this->X / f, this->Y / f, this->Z / f); }
	inline Vector3 operator * (const float& f) const { return Vector3(this->X * f, this->Y * f, this->Z * f); }
	inline Vector3 operator * (const Vector3& v) const { return Vector3(this->X * v.X, this->Y * v.Y, this->Z * v.Z); }
	inline bool operator == (const Vector3& p) const { return this->X == p.X && this->Y == p.Y && this->Z == p.Z; }
	inline bool operator != (const Vector3& p) const { return this->X != p.X || this->Y != p.Y || this->Z != p.Z; }
	inline Vector3& operator += (const Vector3& v) { this->X += v.X, this->Y += v.Y, this->Z += v.Z; return *this; }
	inline Vector3& operator *= (const Vector3& v) { this->X *= v.X, this->Y *= v.Y, this->Z *= v.Z; return *this; }
	inline Vector3 operator -() const {return Vector3(-this->X, -this->Y, -this->Z);}
	~Vector3();
};

#endif 

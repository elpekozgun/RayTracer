#ifndef MATRIX3_H
#define MATRIX3_H

#include "Vector3.h"

class Matrix3
{
	Vector3 rows[3];


public:
	Matrix3();
	Matrix3(Vector3 r1, Vector3 r2, Vector3 r3); 
	Matrix3(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33);
	~Matrix3();

	float Determinant();
	inline Vector3 operator * (const Vector3& vec) const 
	{  
		auto x = rows[0].X * vec.X + rows[0].Y + vec.Y + rows[0].Z * vec.Z;
		auto y = rows[1].X * vec.X + rows[1].Y + vec.Y + rows[1].Z * vec.Z;
		auto z = rows[2].X * vec.X + rows[2].Y + vec.Y + rows[2].Z * vec.Z;
		return Vector3(x,y,z);
	}

	inline Matrix3 operator * (const Matrix3& M) const
	{
		auto m11 = rows[0].X + M.rows[0].X + rows[0].Y * M.rows[1].X + rows[0].Z * M.rows[2].X;
		auto m21 = rows[1].X + M.rows[0].X + rows[1].Y * M.rows[1].X + rows[1].Z * M.rows[2].X;
		auto m31 = rows[2].X + M.rows[0].X + rows[2].Y * M.rows[1].X + rows[2].Z * M.rows[2].X;
		auto m12 = rows[0].X + M.rows[0].Y + rows[0].Y * M.rows[1].Y + rows[0].Z * M.rows[2].Y;
		auto m22 = rows[1].X + M.rows[0].Y + rows[1].Y * M.rows[1].Y + rows[1].Z * M.rows[2].Y;
		auto m32 = rows[2].X + M.rows[0].Y + rows[2].Y * M.rows[1].Y + rows[2].Z * M.rows[2].Y;
		auto m13 = rows[0].X + M.rows[0].Z + rows[0].Y * M.rows[1].Z + rows[0].Z * M.rows[2].Z;
		auto m23 = rows[1].X + M.rows[0].Z + rows[1].Y * M.rows[1].Z + rows[1].Z * M.rows[2].Z;
		auto m33 = rows[2].X + M.rows[0].Z + rows[2].Y * M.rows[1].Z + rows[2].Z * M.rows[2].Z;

		return Matrix3(m11, m12, m13, m21, m22, m23, m31, m32, m33);
	}
private:

};


#endif 



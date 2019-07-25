#include "Matrix3.h"

Matrix3::Matrix3()
{
}

Matrix3::Matrix3(Vector3 r1, Vector3 r2, Vector3 r3)
{
	rows[0] = r1;
	rows[1] = r2;
	rows[2] = r3;
}

Matrix3::Matrix3(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33)
{
	rows[0] = Vector3 { m11,m12,m13 };
	rows[1] = Vector3 { m21,m22,m23 };
	rows[2] = Vector3 { m31,m32,m33 };

}

Matrix3::~Matrix3()
{
}

float Matrix3::Determinant()
{
	float det = (rows[0].X * (rows[1].Y * rows[2].Z - rows[1].Z * rows[2].Y)) -
				(rows[0].Y * (rows[1].X * rows[2].Z - rows[1].Z * rows[2].X)) +
				(rows[0].Z * (rows[1].X * rows[2].Y - rows[1].Y * rows[2].X));
	return det;
}

#include "Triangle.h"

Triangle::Triangle()
{
	Vertices[0] = Vector3();
	Vertices[1] = Vector3();
	Vertices[2] = Vector3();

	Id = -1;
	MaterialId = -1;
}

Triangle::Triangle(int id, int materialId, Vector3 vertices[3])
{
	Id= id;
	MaterialId = materialId;
	Vertices[0] = vertices[0];
	Vertices[1] = vertices[1];
	Vertices[2] = vertices[2];

}

Triangle
::~Triangle()
{
	//std::cout << "Triangle "  << Id << " deleted" << std::endl;
}

Vector3 Triangle::GetCenter()
{
	return Vector3
	(
		(Vertices[0].X + Vertices[1].X + Vertices[2].X) / 3,
		(Vertices[0].Y + Vertices[1].Y + Vertices[2].Y) / 3,
		(Vertices[0].Z + Vertices[1].Z + Vertices[2].Z) / 3
	);
}

Vector3 Triangle::GetNormal(Vector3 point)
{
	return (Vertices[1] - Vertices[0]).CrossProduct(Vertices[2] - Vertices[0]).Normalized();
}

IGeometricEntity* Triangle::Intersect(Ray ray, float& t)
{
	auto a = Vertices[0];
	auto b = Vertices[1];
	auto c = Vertices[2];
	auto d = ray.direction;
	auto o = ray.origin;

	auto A = Matrix3
	(
		Vector3(a.X - b.X, a.X - c.X, d.X),
		Vector3(a.Y - b.Y, a.Y - c.Y, d.Y),
		Vector3(a.Z - b.Z, a.Z - c.Z, d.Z)
	);
	float detA = A.Determinant();
	float detAinv = 1 / detA;

	auto BetaMat = Matrix3
	(
		Vector3(a.X - o.X, a.X - c.X, d.X),
		Vector3(a.Y - o.Y, a.Y - c.Y, d.Y),
		Vector3(a.Z - o.Z, a.Z - c.Z, d.Z)
	);
	float beta = BetaMat.Determinant() * detAinv;
	if(beta < -0.0000001f || beta > 0.99999999f)
	{
		t = 0;
		return NULL;
	}

	auto gammaMat = Matrix3
	(
		Vector3(a.X - b.X, a.X - o.X, d.X),
		Vector3(a.Y - b.Y, a.Y - o.Y, d.Y),
		Vector3(a.Z - b.Z, a.Z - o.Z, d.Z)
	);
	float gamma = gammaMat.Determinant() * detAinv;
	if(gamma < -0.0000001f || gamma > 0.99999999f)
	{
		t = 0;
		return NULL;
	}

	auto tMat = Matrix3
	(
		Vector3(a.X - b.X, a.X - c.X, a.X - o.X),
		Vector3(a.Y - b.Y, a.Y - c.Y, a.Y - o.Y),
		Vector3(a.Z - b.Z, a.Z - c.Z, a.Z - o.Z)
	);
	float tCalc = tMat.Determinant() * detAinv;

	if(beta + gamma < 1)
	{
		t = tCalc;
		return this;
	}

	t = 0;
	return NULL;
}

eEntityType Triangle::GetType()
{
	return eEntityType::triangle;
}

int Triangle::ID()
{
	return Id;
}

int Triangle::MaterialID()
{
	return MaterialId;
}



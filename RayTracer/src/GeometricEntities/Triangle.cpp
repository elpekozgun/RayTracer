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

std::pair<float, IGeometricEntity*> Triangle::Intersect(Ray ray)
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
	
	auto BetaMat = Matrix3
	(
		Vector3(a.X - o.X, a.X - c.X, d.X),
		Vector3(a.Y - o.Y, a.Y - c.Y, d.Y),
		Vector3(a.Z - o.Z, a.Z - c.Z, d.Z)
	);
	float beta = BetaMat.Determinant() / detA;
	if(beta < -0.0000001f || beta > 0.99999999f)
	{
		return std::pair<float, IGeometricEntity*>(0, NULL);;
	}

	auto gammaMat = Matrix3
	(
		Vector3(a.X - b.X, a.X - o.X, d.X),
		Vector3(a.Y - b.Y, a.Y - o.Y, d.Y),
		Vector3(a.Z - b.Z, a.Z - o.Z, d.Z)
	);
	float gamma = gammaMat.Determinant() / detA;
	if(gamma < -0.0000001f || gamma > 0.99999999f)
	{
		return std::pair<float, IGeometricEntity*>(0, NULL);;
	}

	auto tMat = Matrix3
	(
		Vector3(a.X - b.X, a.X - c.X, a.X - o.X),
		Vector3(a.Y - b.Y, a.Y - c.Y, a.Y - o.Y),
		Vector3(a.Z - b.Z, a.Z - c.Z, a.Z - o.Z)
	);
	float t = tMat.Determinant() / detA;

	if(beta + gamma < 1)
	{
		return std::pair<float, IGeometricEntity*>(t,this);
	}

	return std::pair<float, IGeometricEntity*>(0, NULL);;
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



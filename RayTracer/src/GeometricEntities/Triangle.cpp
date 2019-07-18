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

Vector3 Triangle::GetNormal(Vector3 point)
{
	return (Vertices[1] - Vertices[0]).CrossProduct(Vertices[2] - Vertices[0]).Normalized();
}

float Triangle::Intersect2(Ray ray)
{
	/*Vector3 normal = (Vertices[1] - Vertices[0]).CrossProduct(Vertices[2] - Vertices[0]).Normalized();
	Vector3 pointOnPlane = Vertices[0];
	Plane plane(normal, pointOnPlane);

	auto t = plane.Intersect(ray);
	auto hitPoint = ray.origin + ray.direction * t;



	if(IsInsideTriangle(hitPoint, Vertices[0], Vertices[1], Vertices[2]))
	{
		return t;
	}
	*/
	return 0;
}

float Triangle::Intersect(Ray ray)
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
	if(beta > 1 || beta < 0)
	{
		return 0;
	}

	auto gammaMat = Matrix3
	(
		Vector3(a.X - b.X, a.X - o.X, d.X),
		Vector3(a.Y - b.Y, a.Y - o.Y, d.Y),
		Vector3(a.Z - b.Z, a.Z - o.Z, d.Z)
	);
	float gamma = gammaMat.Determinant() / detA;
	if(gamma > 1 || gamma < 0)
	{
		return 0;
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
		return t;
	}

	return 0;
}

eEntityType Triangle::GetType()
{
	return eEntityType::triangle;
}

bool Triangle::OnTheSameSide(Vector3 p, Vector3 v1, Vector3 v2, Vector3 v0)
{
	auto cp1 = (p - v0).CrossProduct(v2 - v0);
	auto cp2 = (v1 - v0).CrossProduct(v2 - v0);
	return cp1.DotProduct(cp2) > 0;
}

bool Triangle::IsInsideTriangle(Vector3 p, Vector3 v1, Vector3 v2, Vector3 v0)
{
	return OnTheSameSide(p, v1, v2, v0) && OnTheSameSide(p, v2, v1, v0) && OnTheSameSide(p, v0 , v1, v2);
}

int Triangle::ID()
{
	return Id;
}

int Triangle::MaterialID()
{
	return MaterialId;
}



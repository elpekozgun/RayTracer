#include "Mesh.h"


Mesh::Mesh()
{
	Id = -1;
	MaterialId = -1;
	Triangles = std::vector<Triangle>{};
}

Mesh::Mesh(int id,int materialID)
{
	Id = id;
	MaterialId = materialID;
	std::vector<Triangle> Triangles;
}

Mesh::~Mesh()
{
	 std::cout << "mesh deleted" << std::endl;
}

float Mesh::Intersect(Ray ray)
{
	float tMin = INFINITY;
	float t = 0;

	for(auto& triangle : this->Triangles)
	{
		t = triangle.Intersect(ray);
		if(t > 0 && t <= tMin)
		{
			tMin = t;
			hitObjectNormal = triangle.GetNormal(Vector3());
		}
	}
	return t;
}

Vector3 Mesh::GetNormal(Vector3 point)
{
	return hitObjectNormal;
}

eEntityType Mesh::GetType()
{
	return eEntityType::mesh;
}

int Mesh::ID()
{
	return Id;
}

int Mesh::MaterialID()
{
	return MaterialId;
}



